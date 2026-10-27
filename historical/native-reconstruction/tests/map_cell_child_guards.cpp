// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellChildren.hpp"
#include <stdexcept>
using namespace ra2;
template<class F>void refused(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("Unsafe map child domain accepted");}
int main(){
    MapAttributeLookup world;refused([&]{mapAttributeCell({},world);});
    std::vector<MapCellInput*> cells(262144);world.cells=cells;refused([&]{mapAttributeCell({},world);});
    MapCellInput fallback;world.fallback=&fallback;
    // Missing/outside pointer lookups must preserve the chosen fallback's data.
    fallback.tile=91;auto& result=mapAttributeCell({-1,0},world);
    if(&result!=&fallback||fallback.position!=MapInputPosition{-1,0}||fallback.tile!=91)throw std::runtime_error("Fallback lookup boundary changed");
    MapCellInput cell;cell.land=-1;
    refused([&]{emptyCellPassability(cell,true,{});});
    cell.land=11;refused([&]{emptyCellPassability(cell,true,std::array<float,11>{});});
    MapLATSettings settings;settings.fill(-1);settings[9]=100;settings[10]=200;
    std::array<MapInputPosition,8> dirs{};cell.tile=100;cell.slope=0;
    refused([&]{setupMapLAT(cell,settings,dirs,world,10);});
}
