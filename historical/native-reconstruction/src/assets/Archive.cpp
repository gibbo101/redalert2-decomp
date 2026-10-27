// SPDX-License-Identifier: GPL-3.0-or-later
// MIX layout/hash/key encoding informed by OpenRA; see THIRD_PARTY.md.
#include "assets/Archive.hpp"
#include "assets/ArchiveSequence.hpp"
#define OPENSSL_SUPPRESS_DEPRECATED
#include <openssl/bn.h>
#include <openssl/blowfish.h>
#include <zlib.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <limits>
#include <cstdio>

namespace ra2 {
std::string lower(std::string s) { for(char& c:s) c=char(std::tolower(static_cast<unsigned char>(c)));return s; }
Data readFile(const std::filesystem::path& path) {
    std::ifstream f(path,std::ios::binary|std::ios::ate);
    if(!f) throw std::runtime_error("Cannot read "+path.string());
    auto end=f.tellg();
    if(end<0 || end>std::streamoff(1024ULL*1024*1024)) throw std::runtime_error("Asset exceeds 1 GiB bound");
    Bytes b(static_cast<std::size_t>(end));f.seekg(0);
    if(!f.read(reinterpret_cast<char*>(b.data()),std::streamsize(b.size()))) throw std::runtime_error("Short read: "+path.string());
    return Data(std::move(b));
}
std::uint32_t mixHash(std::string name) {
    for(char& c:name) c=char(std::toupper(static_cast<unsigned char>(c)));
    const auto n=name.size(), r=n%4;
    if(r) {name.push_back(char(r));name.append(3-r,name[n-r]);}
    return std::uint32_t(crc32(0,reinterpret_cast<const Bytef*>(name.data()),uInt(name.size())));
}
const MixEntry* findMixEntry(std::span<const MixEntry> entries, std::uint32_t id) {
    std::size_t begin=0, count=entries.size();
    const auto key=std::bit_cast<std::int32_t>(id);
    while(count) {
        const auto half=count/2, middle=begin+half;
        const auto candidate=std::bit_cast<std::int32_t>(entries[middle].id);
        if(candidate==key) return &entries[middle];
        if(candidate>key) count=half;
        else {begin=middle+1;count-=half+1;}
    }
    return nullptr;
}
std::vector<std::string> baseMixBootstrapNames(const std::array<bool,100>& expansions) {
    std::vector<std::string> names;
    for(int i=99;i>=0;--i) if(expansions[std::size_t(i)]) {
        char name[16];std::snprintf(name,sizeof(name),"expand%02d.mix",i);
        names.emplace_back(name);
    }
    for(const char* name:{"ra2.mix","cache.mix","local.mix"}) names.emplace_back(name);
    return names;
}
static Bytes mixKey(const Data& d) {
    // Public MIX format RSA modulus (DER INTEGER payload), not a private key.
    constexpr unsigned char modulus[] = {
      0x51,0xbc,0xda,0x08,0x6d,0x39,0xfc,0xe4,0x56,0x51,0x60,0xd6,0x51,0x71,0x3f,0xa2,
      0xe8,0xaa,0x54,0xfa,0x66,0x82,0xb0,0x4a,0xab,0xdd,0x0e,0x6a,0xf8,0xb0,0xc1,0xe6,
      0xd1,0xfb,0x4f,0x3d,0xaa,0x43,0x7f,0x15};
    using BN=std::unique_ptr<BIGNUM,decltype(&BN_free)>;
    BN n(BN_bin2bn(modulus,40,nullptr),BN_free), e(BN_new(),BN_free), out(BN_new(),BN_free);
    std::unique_ptr<BN_CTX,decltype(&BN_CTX_free)> ctx(BN_CTX_new(),BN_CTX_free);
    if(!n||!e||!out||!ctx||!BN_set_word(e.get(),65537)) throw std::runtime_error("MIX RSA setup failed");
    Bytes key;
    for(std::size_t p: {4u,44u}) {
        BN in(BN_lebin2bn(d.ptr(p,40),40,nullptr),BN_free);
        unsigned char result[40]{};
        if(!in||!BN_mod_exp(out.get(),in.get(),e.get(),n.get(),ctx.get())||BN_bn2lebinpad(out.get(),result,40)!=40)
            throw std::runtime_error("MIX key decoding failed");
        key.insert(key.end(),result,result+39);
    }
    key.resize(56);return key;
}
Mix::Mix(Data data):data_(std::move(data)) {
    std::size_t off=data_.u16(0) ? 0 : 4;
    if(off) {checksum_=(data_.u32(0)&0x10000)!=0;encrypted_=(data_.u32(0)&0x20000)!=0;}
    Data header;
    if(off && (data_.u32(0)&0x20000)) {
        const auto key=mixKey(data_);BF_KEY fish{};BF_set_key(&fish,int(key.size()),key.data());
        Bytes first(8);BF_ecb_encrypt(data_.ptr(84,8),first.data(),&fish,BF_DECRYPT);
        const auto count=Data(first).u16(0);
        if(count>32767) throw std::runtime_error("Negative original MIX file count is unsupported");
        const std::size_t length=(6+12*std::size_t(count)+7)&~std::size_t(7);
        data_.check(84,length);Bytes decoded(length);
        for(std::size_t p=0;p<length;p+=8) BF_ecb_encrypt(data_.ptr(84+p,8),decoded.data()+p,&fish,BF_DECRYPT);
        header=Data(std::move(decoded));body_=84+length;
    } else {
        const auto count=data_.u16(off);
        if(count>32767) throw std::runtime_error("Negative original MIX file count is unsupported");
        body_=off+6+12*std::size_t(count);
        header=data_.slice(off,body_-off);
    }
    const auto count=header.u16(0);const auto size=header.u32(2);data_.check(body_,size);
    bodySize_=size;
    for(std::size_t i=0;i<count;++i) {
        const auto p=6+12*i;const auto id=header.u32(p), start=header.u32(p+4), length=header.u32(p+8);
        if(start>size || length>size-start) throw std::runtime_error("MIX entry exceeds data body");
        if(!entries_.empty() && std::bit_cast<std::int32_t>(entries_.back().id)>std::bit_cast<std::int32_t>(id))
            throw std::runtime_error("MIX index is not in original signed ID order");
        entries_.push_back({id,start,length});
    }
}
std::optional<Data> Mix::find(const std::string& name) const {
    const auto* entry=findMixEntry(entries_,mixHash(name));if(!entry) return std::nullopt;
    return data_.slice(body_+entry->offset,entry->length);
}
AssetStore::AssetStore(const std::filesystem::path& root,Registration registration):root_(root) {
    if(!std::filesystem::is_directory(root)) throw std::runtime_error("Game data directory does not exist: "+root.string());
    for(const auto& f:std::filesystem::directory_iterator(root)) if(f.is_regular_file()) {
        if(!files_.emplace(lower(f.path().filename().string()),f.path()).second)
            throw std::runtime_error("Ambiguous case-insensitive game filename");
    }
    auto it=files_.find("ra2.mix");
    if(it==files_.end()) throw std::runtime_error("ra2.mix missing; supply your base RA2 installation (see README.md)");
    auto append=[&](const Data& data,const std::string& name,const std::filesystem::path& file) {
        archives_.emplace_back(data);
        sources_.push_back({name,file,data.offset,data.offset+archives_.back().bodyOffset()});
    };
    if(registration==Registration::InitialTemperate) {
        // Bounded initial base startup. Directory ordering is a deterministic host
        // adapter, not a claim about unobserved Windows FindFirst/FindNext order.
        auto request=[&](const std::string& name) {
            if(auto match=resolve(name)) {append(match->data,name,match->file);return true;}
            return false;
        };
        request("language.mix");
        std::array<bool,100> expansions{};
        for(unsigned n=0;n<100;++n) {char name[16];std::snprintf(name,sizeof(name),"expand%02u.mix",n);expansions[n]=files_.contains(name);}
        for(const auto& name:baseMixBootstrapNames(expansions)) request(name);
        std::vector<std::string> maps,movies;
        for(const auto& [name,path]:files_) {
            if(name.ends_with(".mix")&&name.starts_with("maps")) maps.push_back(name);
            if(name.ends_with(".mix")&&name.starts_with("movies")) movies.push_back(name);
        }
        const auto startup=startupMixRequests(true,0,maps,movies,[&](const auto& name){return resolve(name).has_value();});
        for(const auto& name:startup.names) request(name);
        // The prototype does not consume movie data. Missing movies are an
        // explicit bounded host omission; required visual/game assets still fail.
        if(std::find(startup.names.begin(),startup.names.end(),"multi.mix")==startup.names.end())
            throw std::runtime_error("Initial base archive registration requires conquer/cameo/maps/multi");
        for(const auto& name:theaterMixRequests(0,-1)) request(name);
        return;
    }
    Mix rootMix(readFile(it->second));
    // Explicit base-game scope and load order. Expansion/patch merging is deferred.
    for(const char* name:{"local.mix","cache.mix","conquer.mix","generic.mix","isotemp.mix","temperat.mix"}) {
        auto data=rootMix.find(name);if(data) append(*data,name,it->second);
    }
    sources_.push_back({"ra2.mix",it->second,0,rootMix.bodyOffset()});
    archives_.push_back(std::move(rootMix));
    for(const char* name:{"multi.mix","maps01.mix","maps02.mix"}) {
        auto p=files_.find(name);if(p!=files_.end()) append(readFile(p->second),name,p->second);
    }
}
std::optional<AssetStore::Match> AssetStore::resolve(const std::string& name) const {
    // Leaf names only. Loose user files are read-only overrides, never written.
    if(name.find('/')!=std::string::npos || name.find('\\')!=std::string::npos || name=="..")
        throw std::runtime_error("Asset name must be a leaf filename");
    auto it=files_.find(lower(name));if(it!=files_.end()) return Match{readFile(it->second),it->second,std::nullopt};
    for(std::size_t i=0;i<archives_.size();++i) if(auto d=archives_[i].find(name)) return Match{*d,sources_.at(i).file,i};
    return std::nullopt;
}
std::optional<Data> AssetStore::find(const std::string& name) const {
    if(auto match=resolve(name)) return match->data;
    return std::nullopt;
}
Data AssetStore::require(const std::string& name) const {
    auto d=find(name);if(!d) throw std::runtime_error("Required original asset missing: "+name);return *d;
}
}
