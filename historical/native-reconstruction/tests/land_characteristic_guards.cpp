// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/LandCharacteristics.hpp"
#include <bit>
#include <iostream>
using namespace ra2;
int main(){try{
    for(unsigned missing=0;missing<3;++missing) {
        std::array<LandCharacteristic,12> table;
        for(auto& row:table){row.speed.fill(std::bit_cast<float>(0x13572468u));row.buildable=231;}
        unsigned calls=0;
        LandCharacteristicServices services;
        if(missing!=0)services.hasSection=[&](unsigned){++calls;return true;};
        if(missing!=1)services.readSpeed=[&](unsigned,LandSpeed,double){++calls;return 0.5;};
        if(missing!=2)services.readBuildable=[&](unsigned,std::uint8_t){++calls;return std::uint8_t(0);};
        bool refused=false;
        try{loadLandCharacteristics(table,services);}catch(const std::invalid_argument&){refused=true;}
        if(!refused||calls)throw std::runtime_error("Missing services were not refused before mutation");
        for(const auto& row:table){
            for(auto f:row.speed)if(std::bit_cast<std::uint32_t>(f)!=0x13572468u)throw std::runtime_error("Refusal changed initial speed");
            if(row.buildable!=231)throw std::runtime_error("Refusal changed Buildable");
        }
    }
    std::cout<<"Land characteristic service guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
