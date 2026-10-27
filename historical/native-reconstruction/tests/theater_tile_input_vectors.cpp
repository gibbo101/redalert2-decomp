// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TheaterTileInputs.hpp"
#include <openssl/evp.h>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace ra2;
namespace {
void word(std::vector<std::uint8_t>& b,std::uint32_t v){for(int i=0;i<4;++i)b.push_back(std::uint8_t(v>>(i*8)));}
std::string digest(const std::vector<std::uint8_t>& b){unsigned char h[EVP_MAX_MD_SIZE];unsigned n=0;
    if(!EVP_Digest(b.data(),b.size(),h,&n,EVP_sha256(),nullptr))throw std::runtime_error("Digest failed");
    std::ostringstream s;for(unsigned i=0;i<n;++i)s<<std::hex<<std::setfill('0')<<std::setw(2)<<unsigned(h[i]);return s.str();}
}
int main(){try{
    std::string line;while(std::getline(std::cin,line)){
        std::istringstream in(line);char op=0;unsigned count=0;in>>op>>count;
        if(op!='T'||count>1024)throw std::invalid_argument("Unknown theater projection command");
        std::array<int,16> numbers{};for(auto& n:numbers)in>>n;
        std::vector<TheaterTileSetInput> sets(count);
        for(auto& set:sets){unsigned flags=0;in>>set.count>>set.lastCount>>set.marble>>set.nonMarble>>set.toSnow>>set.toTemperate>>flags>>set.shadowTiles;
            if(flags>63)throw std::invalid_argument("Theater flags outside profile");
            set.morphable=flags&1;set.allowPlace=flags&2;set.allowBurrowing=flags&4;
            set.allowTiberium=flags&8;set.requiredForRMG=flags&16;set.shadowCaster=flags&32;
        }
        if(!in)throw std::invalid_argument("Incomplete theater projection command");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing theater projection command");
        const auto result=prepareTheaterTileInputs(numbers,sets);
        std::vector<std::uint8_t> bytes;
        for(auto n:result.depthBases)word(bytes,unsigned(n));
        word(bytes,unsigned(result.setStarts.size()));for(auto n:result.setStarts)word(bytes,unsigned(n));
        word(bytes,unsigned(result.shifts.size()));for(auto shift:result.shifts){word(bytes,unsigned(shift.first));word(bytes,unsigned(shift.delta));}
        word(bytes,unsigned(result.types.size()));
        for(auto& t:result.types)for(auto n:{t.index,t.setBase,t.marble,t.nonMarble,t.toSnow,t.toTemperate,
            int(t.morphable),int(t.shadowCaster),int(t.allowPlace),int(t.requiredForRMG),int(t.allowBurrowing),int(t.allowTiberium)})word(bytes,unsigned(n));
        std::cout<<result.types.size()<<' '<<digest(bytes)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
