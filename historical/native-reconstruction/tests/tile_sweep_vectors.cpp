// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileSweep.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
using namespace ra2;
namespace {
std::array<std::uint8_t,32> hash(const std::uint8_t* data,std::size_t size){std::array<std::uint8_t,32> out{};unsigned n=0;
    if(!EVP_Digest(data,size,out.data(),&n,EVP_sha256(),nullptr)||n!=32)throw std::runtime_error("Digest failed");return out;}
std::string hex(const std::array<std::uint8_t,32>& h){std::ostringstream s;for(auto c:h)s<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(c);return s.str();}
std::string digest(const std::vector<std::uint32_t>& values){Bytes b;for(auto n:values)for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));return hex(hash(b.data(),b.size()));}
Bytes decode(const std::string& s){if(s.empty()||s.size()%2)throw std::invalid_argument("Bad hex");Bytes b;
    for(std::size_t i=0;i<s.size();i+=2){std::size_t n=0;auto v=std::stoul(s.substr(i,2),&n,16);if(n!=2)throw std::invalid_argument("Bad hex");b.push_back(std::uint8_t(v));}return b;}
std::string text(const std::string& s){if(s=="-")return {};auto b=decode(s);return {b.begin(),b.end()};}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;int width=0,clear=0;unsigned force=0,keep=0,initialized=0,disabled=0;TileSweepCursor cursor;OriginalRandomState random;TileVariantCache cache;TileVariantTables tables;
        in>>op>>width>>force>>keep>>clear>>cursor.x>>cursor.y>>cursor.remaining>>cursor.index>>initialized>>disabled>>random.next1>>random.next2;
        if(op!='S'||force>255||keep>255||initialized>255||disabled>255)throw std::invalid_argument("Unknown sweep profile");
        random.disabled=std::uint8_t(disabled);cache.initialized=std::uint8_t(initialized);
        for(auto& n:random.table)in>>n;for(auto& n:cache.large)in>>n;for(auto& n:tables.small)in>>n;for(auto& d:tables.neighbors)in>>d[0]>>d[1];
        unsigned count=0;in>>count;if(count>1024)throw std::invalid_argument("Too many primary types");std::vector<int> primary(count);for(auto& n:primary)in>>n;
        in>>count;if(count>1024)throw std::invalid_argument("Too many types");std::vector<TileSweepType> types(count);
        struct Source {int id=-1;bool resident=false,prepared=false;};std::vector<Source> sources(count);
        for(unsigned i=0;i<count;++i){auto& t=types[i];unsigned lazy=0,required=0,owned=0,resident=0,prepared=0;std::string name;
            in>>t.next>>t.variants>>t.usage>>lazy>>required>>owned>>name>>sources[i].id>>resident>>prepared;
            if(lazy>255||required>255||owned>255||resident>1||prepared>1)throw std::invalid_argument("Bad type byte");
            t.lazy=std::uint8_t(lazy);t.requiredForRMG=std::uint8_t(required);t.owned=std::uint8_t(owned);t.filename=text(name);sources[i].resident=resident;sources[i].prepared=prepared;
        }
        in>>count;if(count>20000)throw std::invalid_argument("Too many cells");std::vector<TileSweepCell> cells(count);std::vector<int> slots(512*512,-1);
        for(unsigned i=0;i<count;++i){auto& c=cells[i];int x=0,y=0,sub=0;in>>x>>y>>c.tile>>sub>>c.flags;
            if(x<0||x>=512||y<0||y>=512||sub<0||sub>255||slots[std::size_t(y)*512+std::size_t(x)]!=-1)throw std::invalid_argument("Bad cell fixture");
            c.position={std::int16_t(x),std::int16_t(y)};c.sub=std::uint8_t(sub);slots[std::size_t(y)*512+std::size_t(x)]=int(i);
        }
        in>>count;if(count>64)throw std::invalid_argument("Too many files");std::vector<Data> files;std::map<std::string,Data> named;
        for(unsigned i=0;i<count;++i){std::string name,data;in>>name>>data;Data bytes{decode(data)};if(!named.emplace(text(name),bytes).second)throw std::invalid_argument("Duplicate file");files.push_back(bytes);}
        if(!in)throw std::invalid_argument("Incomplete sweep fixture");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing sweep fixture");
        for(std::size_t i=0;i<types.size();++i){auto s=sources[i];if(s.resident||s.prepared){if(s.id<0||std::size_t(s.id)>=files.size())throw std::invalid_argument("Bad image source");
                if(s.resident)types[i].image=files[std::size_t(s.id)];if(s.prepared)types[i].prepared=prepareTileImage(files[std::size_t(s.id)]);}}
        std::vector<std::uint32_t> visits,usage,releases;Bytes requests;unsigned calls=0;
        TileSweepObserver observer{[&](int n){visits.push_back(std::uint32_t(n));},[&](int n,std::uint32_t v){usage.push_back(unsigned(n));usage.push_back(v);},[&](int n){releases.push_back(unsigned(n));}};
        const auto result=sweepTileImages(width,slots,cells,primary,types,clear,cursor,std::uint8_t(force),std::uint8_t(keep),cache,tables,
            [&]{++calls;return nextOriginalRandom(random);},[&](const std::string& name){requests.insert(requests.end(),name.begin(),name.end());requests.push_back(0);return named.at(name);},observer);
        std::vector<std::uint32_t> state;
        for(const auto& t:types){const auto* p=t.prepared?&*t.prepared:nullptr;
            state.insert(state.end(),{t.usage,t.owned,unsigned(bool(t.image)),p?unsigned(p->typeColumns):0,p?unsigned(p->typeRows):0,p?unsigned(p->colorRamps.size()):0});
            if(t.image){auto h=hash(t.image->ptr(),t.image->size);for(unsigned i=0;i<32;i+=4)state.push_back(std::uint32_t(h[i])|(std::uint32_t(h[i+1])<<8)|(std::uint32_t(h[i+2])<<16)|(std::uint32_t(h[i+3])<<24));}
            if(p)for(auto& ramp:p->colorRamps){state.push_back(unsigned(bool(ramp)));if(ramp)for(auto n:*ramp)state.push_back(n);}
        }
        std::vector<std::uint32_t> randomState{random.disabled,unsigned(random.next1),unsigned(random.next2)};randomState.insert(randomState.end(),random.table.begin(),random.table.end());
        std::vector<std::uint32_t> cacheState{cache.initialized};for(auto n:cache.large)cacheState.push_back(unsigned(n));
        std::cout<<result.loaded<<' '<<result.bytes<<' '<<std::uint32_t(result.kibibytes)<<' '
          <<digest({unsigned(result.cursor.x),unsigned(result.cursor.y),unsigned(result.cursor.remaining),result.cursor.index})<<' '<<digest(state)<<' '<<digest(visits)<<' '
          <<digest(usage)<<' '<<digest(releases)<<' '<<hex(hash(requests.data(),requests.size()))<<' '<<digest(randomState)<<' '<<digest(cacheState)<<' '<<calls<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
