// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantrySpeed.hpp"
#include <array>
#include <bit>
#include <cfenv>
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace ra2;
struct Fields {
    int base=32;float country=1;double multiplier=1,percentage=1,veterancy=0,rules=1.5;
    std::uint8_t flag=0,typeFlag=0,veteran=0,elite=0;
    InfantrySpeedActor actor(){return {veterancy,percentage,multiplier,flag};}
    InfantrySpeedType type(){return {base,veteran,elite,typeFlag};}
};
void guards(){
    Fields f;int types=0,countries=0,rules=0;
    InfantrySpeedServices s{[&]{++types;return f.type();},[&]()->const float&{++countries;return f.country;},
        [&]()->const double&{++rules;return f.rules;},{}};
    const auto check=[&](int want){if(infantrySpeed(f.actor(),s)!=want)throw std::runtime_error("Live Infantry speed differs");};
    check(32);f.base=31;f.percentage=.5;check(15);f.flag=255;check(22);f.typeFlag=128;check(10);
    f.flag=0;f.percentage=1;f.veterancy=2;f.elite=1;check(46);f.rules=.5;check(15);
    if(types!=16||countries!=6||rules!=2)throw std::runtime_error("Infantry repeated query counts differ");
    f.veterancy=0;s.veteranSpeed598={};check(31);f.veterancy=2;
    bool refused=false;try{check(31);}catch(const std::invalid_argument&){refused=true;}
    if(!refused)throw std::runtime_error("Promoted speed accepted missing rules");
    f.veterancy=0;f.base=1;f.country=1;f.multiplier=2147483648.;check(INT32_MIN);
    f.multiplier=9223372036854775808.;check(0);f.multiplier=std::bit_cast<double>(0x7ff8123456789abcULL);check(0);
    for(int mode:{FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO,FE_TONEAREST}){
        std::fesetround(mode);check(0);if(std::fegetround()!=mode)throw std::runtime_error("Infantry speed leaked FP mode");
    }
    std::cout<<"Infantry live owners, repeated queries, conversion and FP guards PASS\n";
}
int main(int argc,char** argv){try{
    if(argc==2&&std::string(argv[1])=="--guards"){guards();return 0;}
    if(argc!=1)throw std::invalid_argument("Unexpected Infantry speed argument");
    const int saved=std::fegetround();std::string line;int sequence=0;
    while(std::getline(std::cin,line)){
        std::istringstream in(line);char command=0;std::array<std::uint64_t,13> v{};in>>command;
        for(auto& x:v)if(!(in>>x))throw std::invalid_argument("Missing speed field");
        std::string extra;if(command!='S'||in>>extra)throw std::invalid_argument("Infantry speed command");
        if(v[0]>UINT32_MAX||v[1]>UINT32_MAX||v[11]>31||v[12]>32)throw std::invalid_argument("Infantry speed input");
        for(int i=7;i<11;++i)if(v[std::size_t(i)]>255)throw std::invalid_argument("Infantry speed byte");
        Fields f;f.base=std::bit_cast<std::int32_t>(std::uint32_t(v[0]));f.country=std::bit_cast<float>(std::uint32_t(v[1]));
        f.multiplier=std::bit_cast<double>(v[2]);f.percentage=std::bit_cast<double>(v[3]);f.veterancy=std::bit_cast<double>(v[4]);f.rules=std::bit_cast<double>(v[5]);
        const auto calls=v[6];if(!calls||calls>16)throw std::invalid_argument("Infantry speed calls");
        f.flag=std::uint8_t(v[7]);f.typeFlag=std::uint8_t(v[8]);f.veteran=std::uint8_t(v[9]);f.elite=std::uint8_t(v[10]);
        int queries=0;const auto trace=[&](char k,int x){
            std::cout<<k<<' '<<x<<' ';
            if(k=='c'||++queries!=int(v[12]))return;
            if(v[11]&1){f.base=17;f.country=.5f;}
            if(v[11]&2){f.multiplier=1.75;f.percentage=.375;}
            if(v[11]&4)f.veterancy=1.5;
            if(v[11]&8){f.flag^=255;f.typeFlag^=128;}
            if(v[11]&16){f.veteran^=1;f.elite^=1;f.rules=2.25;}
        };
        InfantrySpeedServices services{[&]{return f.type();},[&]()->const float&{return f.country;},[&]()->const double&{return f.rules;},trace};
        const auto mode=std::array{FE_UPWARD,FE_DOWNWARD,FE_TOWARDZERO,FE_TONEAREST}[std::size_t(sequence++%4)];std::fesetround(mode);
        for(std::uint64_t i=0;i<calls;++i){queries=0;const int result=infantrySpeed(f.actor(),services);std::cout<<'R'<<' '<<result<<' ';
            if(std::fegetround()!=mode)throw std::runtime_error("Infantry speed leaked FP mode");}
        std::cout<<'Z'<<' '<<std::uint32_t(f.base)<<' '<<std::bit_cast<std::uint32_t>(f.country)<<' '<<std::bit_cast<std::uint64_t>(f.multiplier)<<' '
            <<std::bit_cast<std::uint64_t>(f.percentage)<<' '<<std::bit_cast<std::uint64_t>(f.veterancy)<<' '<<std::bit_cast<std::uint64_t>(f.rules)<<' '
            <<int(f.flag)<<' '<<int(f.typeFlag)<<' '<<int(f.veteran)<<' '<<int(f.elite)<<'\n';
    }
    std::fesetround(saved);return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
