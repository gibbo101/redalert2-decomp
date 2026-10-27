// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitDrawCaller.hpp"
#include <iostream>
using namespace ra2;
int main(){try{
    int refused=0,callbacks=0;
    for(int count:{-1,501}){
        UnitScreenRegistry registry;registry.count=count;
        try{registerUnitScreen(registry,1,{0,0},{0,0},96,88);return 1;}
        catch(const std::invalid_argument&){++refused;}
        if(registry.count!=count)return 2;
    }
    for(int profile=0;profile<4;++profile){
        OrdinaryUnitDrawInputs a;
        if(profile==0)a.type.harvester=1;
        if(profile==1)a.alternate.harvester=255;
        if(profile==2)a.bridge=1;
        if(profile==3)a.flagHouse=0;
        UnitDrawResource resource{};OrdinaryUnitDrawServices s;
        s.loadShape=[&]{++callbacks;return 1u;};
        try{drawOrdinaryUnitCaller(resource,a,{0,0},{0,0,96,88},s);return 3;}
        catch(const std::invalid_argument&){++refused;}
        if(callbacks||resource.flags||resource.shape)return 4;
    }
    if(refused!=6)return 5;
    for(int count:{0,499,500}){
        UnitScreenRegistry registry;registry.count=count;
        registry.entries.fill({11,{13,17}});
        const bool accepted=registerUnitScreen(registry,19,{0,0},{10,20},96,88);
        if(accepted!=(count<500)||registry.count!=count+int(accepted))return 7;
        for(int i=0;i<500;++i){
            const auto& entry=registry.entries[std::size_t(i)];
            if(accepted&&i==count){if(entry.actor!=19||entry.point.x!=10||entry.point.y!=20)return 8;}
            else if(entry.actor!=11||entry.point.x!=13||entry.point.y!=17)return 9;
        }
    }
    std::cout<<"Unrecovered Unit profiles/counts refused; registry live entries and capacity tails preserved: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 6;}}
