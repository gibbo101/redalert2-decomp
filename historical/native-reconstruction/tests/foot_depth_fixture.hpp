// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FootDepth.hpp"
#include "sim/Facing.hpp"
#include <array>
#include <bit>
#include <iostream>
struct DepthFixture {
    unsigned seed=0;
    int x=0,y=0,bridge=0,tileBase=0,invalidX=-32768,invalidY=-32768,count=4;
    std::array<ra2::FootDepthCell,81> cells;
    std::array<bool,81> present{};
    bool logging=true;
    void prepare(){
        auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n));};
        const auto p=ra2::footDepthCoordinates(x,y);
        for(unsigned i=0;i<81;++i){
            auto& c=cells[i];const auto v=(i+1u)*2654435761u+seed*2246822519u;
            c.position={word(int(p.x)+int(i%9)-4),word(int(p.y)+int(i/9)-4)};
            present[i]=!seed||i==40||(v&3)!=0;c.flags=seed?(v>>8)&0x10d00u:0;
            c.tile=seed?(v%8==1?65535:v%8==2?255:ra2::signed32(std::uint32_t(tileBase)+(v>>16)%22)):65535;
            c.level=seed?std::bit_cast<std::int8_t>(std::uint8_t(v>>20)):0;
            c.field116=seed?std::int16_t(int((v>>10)%7)-2):-1;c.fieldEC=seed&&(v&4)?10:0;
        }
    }
    ra2::FootDepthWorld world(){
        ra2::FootDepthWorld w;w.bridge=std::uint8_t(bridge);w.tileBase=tileBase;
        w.invalid={std::bit_cast<std::int16_t>(std::uint16_t(invalidX)),std::bit_cast<std::int16_t>(std::uint16_t(invalidY))};
        w.trace=[&](int i){if(logging)std::cout<<"p"<<i<<' ';};
        w.coordinates=[&]{if(logging)std::cout<<"coords ";return ra2::footDepthCoordinates(x,y);};
        w.cell=[&](ra2::UnitLightCell p)->const ra2::FootDepthCell*{
            if(logging)std::cout<<"cell "<<p.x<<' '<<p.y<<' ';
            for(unsigned i=0;i<81;++i)if(cells[i].position==p)return present[i]?&cells[i]:nullptr;
            return nullptr;
        };
        w.cellPredicate=[&](const ra2::FootDepthCell& c){
            if(logging)std::cout<<"cellpred "<<c.position.x<<' '<<c.position.y<<' ';
            return ra2::footDepthCellPredicate(c,count);
        };
        return w;
    }
};
