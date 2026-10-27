// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TheaterTileFiles.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
using namespace ra2;
namespace {
void word(Bytes& b,std::uint32_t n){for(int i=0;i<4;++i)b.push_back(std::uint8_t(n>>(i*8)));}
std::string digest(const Bytes& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(h[i]);return s.str();}
Bytes decode(const std::string& text){if(text.empty()||text.size()%2)throw std::invalid_argument("Bad hex");Bytes result;
    for(std::size_t i=0;i<text.size();i+=2){std::size_t n=0;auto v=std::stoul(text.substr(i,2),&n,16);if(n!=2)throw std::invalid_argument("Bad hex");result.push_back(std::uint8_t(v));}return result;}
std::string string(const std::string& text){auto b=decode(text);return {b.begin(),b.end()};}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;int theater=0;unsigned count=0;in>>op>>theater>>count;
        if(op!='F'||!count||count>1024)throw std::invalid_argument("Unknown theater file command");
        std::array<int,16> numbers{};for(auto& n:numbers)in>>n;
        std::vector<TheaterTileSetInput> sets(count);std::vector<std::string> prefixes;
        for(auto& set:sets){unsigned flags=0;std::string prefix;in>>set.count>>set.lastCount>>set.marble>>set.nonMarble>>set.toSnow>>set.toTemperate>>flags>>set.shadowTiles>>prefix;
            if(flags>63)throw std::invalid_argument("Bad flags");prefixes.push_back(string(prefix));
            set.morphable=flags&1;set.allowPlace=flags&2;set.allowBurrowing=flags&4;set.allowTiberium=flags&8;set.requiredForRMG=flags&16;set.shadowCaster=flags&32;
        }
        unsigned files=0;in>>files;if(files>1024)throw std::invalid_argument("Too many fixture files");
        std::map<std::string,std::pair<unsigned,Data>> images;
        for(unsigned i=0;i<files;++i){std::string name,data;in>>name>>data;if(!images.emplace(string(name),std::make_pair(i,Data{decode(data)})).second)throw std::invalid_argument("Duplicate file");}
        if(!in)throw std::invalid_argument("Incomplete theater file command");in>>std::ws;if(!in.eof())throw std::invalid_argument("Trailing command");
        Bytes requests;
        const auto r=prepareLoadedTheaterTiles(numbers,sets,prefixes,theater,[&](const std::string& name)->std::optional<Data>{
            requests.insert(requests.end(),name.begin(),name.end());requests.push_back(0);
            auto found=images.find(name);return found==images.end()?std::nullopt:std::optional<Data>{found->second.second};});
        Bytes payload;word(payload,unsigned(r.primary.size()));word(payload,unsigned(r.allTypes.size()));for(auto n:r.primary)word(payload,unsigned(n));
        for(const auto& tile:r.allTypes){const auto& t=tile.type;
            for(auto n:{t.index,t.setBase,t.marble,t.nonMarble,t.toSnow,t.toTemperate,int(t.morphable),int(t.shadowCaster),int(t.allowPlace),int(t.requiredForRMG),int(t.allowBurrowing),int(t.allowTiberium),tile.next,tile.variants,
                tile.image?int(images.at(tile.source).first):-1,tile.image?tile.image->typeColumns:0,tile.image?tile.image->typeRows:0})word(payload,std::uint32_t(n));
            if(tile.image){const auto& image=*tile.image;
                for(auto n:{image.image.columns,image.image.rows,image.image.width,image.image.height})word(payload,unsigned(n));
                for(std::size_t i=0;i<image.subTileOffsets.size();++i){word(payload,image.subTileOffsets[i]);
                    if(image.colorRamps[i])for(auto n:*image.colorRamps[i]){payload.push_back(std::uint8_t(n));payload.push_back(std::uint8_t(n>>8));}}
            }
        }
        std::cout<<r.primary.size()<<' '<<r.allTypes.size()<<' '<<digest(payload)<<' '<<digest(requests)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
