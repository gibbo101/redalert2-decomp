// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/LandCharacteristics.hpp"
#include <openssl/evp.h>
#include <bit>
#include <cfenv>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
using namespace ra2;
namespace {
using Words=std::vector<std::uint32_t>;
std::string digest(const Words& words) {
    std::vector<unsigned char> bytes;
    for(auto n:words)for(unsigned i=0;i<4;++i)bytes.push_back(static_cast<unsigned char>(n>>(8*i)));
    unsigned char h[32];unsigned size=0;
    if(!EVP_Digest(bytes.data(),bytes.size(),h,&size,EVP_sha256(),nullptr)||size!=32)
        throw std::runtime_error("Digest failed");
    std::ostringstream out;
    for(auto b:h)out<<std::hex<<std::setw(2)<<std::setfill('0')<<unsigned(b);
    return out.str();
}
struct Rounding {
    int old=std::fegetround();
    explicit Rounding(unsigned mode) {
        constexpr int modes[]{FE_TONEAREST,FE_DOWNWARD,FE_UPWARD,FE_TOWARDZERO};
        if(mode>3||old==-1||std::fesetround(modes[mode]))throw std::invalid_argument("FP mode unavailable");
    }
    ~Rounding(){std::fesetround(old);}
};
}
int main(){try{
    std::string line;
    while(std::getline(std::cin,line)) {
        std::istringstream in(line);char op=0;unsigned mode=0;in>>op>>mode;
        if(op!='L'||mode>3)throw std::invalid_argument("Invalid land fixture");
        std::array<LandCharacteristic,12> table;
        std::array<std::uint32_t,12> present{},buildable{};
        std::array<std::array<std::array<std::uint64_t,2>,8>,12> reads{};
        for(unsigned s=0;s<12;++s) {
            in>>present[s]>>buildable[s];
            for(auto& f:table[s].speed){std::uint32_t bits=0;in>>bits;f=std::bit_cast<float>(bits);}
            unsigned b=0;in>>b;if(b>255)throw std::invalid_argument("Invalid initial Buildable");table[s].buildable=std::uint8_t(b);
            for(unsigned k:{3,0,1,2,5,6,7})in>>reads[s][k][0]>>reads[s][k][1];
        }
        if(!in)throw std::invalid_argument("Incomplete land fixture");in>>std::ws;
        if(!in.eof())throw std::invalid_argument("Trailing land fixture");
        Words events,state;std::array<std::array<unsigned,8>,12> counts{};
        LandCharacteristicServices services;
        services.hasSection=[&](unsigned s){events.insert(events.end(),{0,s,present[s]});return present[s]!=0;};
        services.readSpeed=[&](unsigned s,LandSpeed key,double fallback) {
            const unsigned k=static_cast<unsigned>(key);auto& count=counts[s][k];
            if(count>1||fallback!=1.0)throw std::runtime_error("Unexpected land read");
            const auto bits=reads[s][k][count++];
            events.insert(events.end(),{1,s,k,0,0x3ff00000u,std::uint32_t(bits),std::uint32_t(bits>>32)});
            return std::bit_cast<double>(bits);
        };
        services.readBuildable=[&](unsigned s,std::uint8_t fallback){
            events.insert(events.end(),{2,s,fallback,buildable[s]});return std::uint8_t(buildable[s]);
        };
        services.store=[&](unsigned s,unsigned field,std::uint32_t n){events.insert(events.end(),{3,s,field,n});};
        const int before=std::fegetround();
        {Rounding rounding(mode);const int supplied=std::fegetround();loadLandCharacteristics(table,services);
            if(std::fegetround()!=supplied)throw std::runtime_error("Land parent changed FP mode");}
        if(std::fegetround()!=before)throw std::runtime_error("Fixture failed FP restoration");
        for(const auto& row:table){for(auto f:row.speed)state.push_back(std::bit_cast<std::uint32_t>(f));state.push_back(row.buildable);}
        std::cout<<digest(state)<<' '<<digest(events)<<'\n';
    }
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
