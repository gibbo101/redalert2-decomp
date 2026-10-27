// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileSweep.hpp"
#include <iostream>
#include <limits>
using namespace ra2;
template<class F>void refused(F f){try{f();}catch(const std::exception&){return;}throw std::runtime_error("Expected safety refusal");}
int main(){try{
    for(int width:{-1,0,1,256,std::numeric_limits<int>::max()})refused([&]{resetTileSweepCursor(width);});
    std::vector<int> slots(512*512,-1);auto c=resetTileSweepCursor(2);
    auto bad=c;bad.x=std::numeric_limits<int>::max();refused([&]{advanceTileSweepCursor(bad,2,slots);});
    bad=c;bad.remaining=-1;refused([&]{advanceTileSweepCursor(bad,2,slots);});
    bad=c;bad.index=0;refused([&]{advanceTileSweepCursor(bad,2,slots);});
    refused([&]{advanceTileSweepCursor(c,2,std::span<const int>(slots).first(4));});
    TileVariantCache cache;cache.initialized=1;TileVariantTables tables;
    std::vector<TileSweepType> types(1);std::vector<int> primary{0};std::vector<TileSweepCell> cells(1);
    auto run=[&](unsigned force){return sweepTileImages(2,slots,cells,primary,types,0,{},std::uint8_t(force),0,cache,tables,{},{});};
    types[0].next=0;refused([&]{run(1);});types[0].next=-1;
    types[0].lazy=1;types[0].filename="MISSING.TEM";refused([&]{run(1);});types[0].lazy=0;
    slots[1025]=0;cells[0].tile=-1;refused([&]{run(0);});
    cells[0].tile=0;primary[0]=-1;refused([&]{run(0);});primary[0]=0;
    types[0].variants=0;refused([&]{run(0);});
    std::cout<<"Tile sweep native domain guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
