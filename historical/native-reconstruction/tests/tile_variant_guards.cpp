// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/TileVariants.hpp"
#include <iostream>
using namespace ra2;
template<class F>void refused(F f){try{f();}catch(const std::exception&){return;}throw std::runtime_error("Expected safety refusal");}
int main(){try{
    OriginalRandomState rng;rng.next1=-1;refused([&]{nextOriginalRandom(rng);});rng.disabled=255;
    if(nextOriginalRandom(rng)!=0||rng.next1!=-1)throw std::runtime_error("Disabled RNG changed state");
    TileVariantTables tables;TileVariantCache cache;cache.initialized=2;TileVariantImage image;
    refused([&]{selectTileVariant(cache,tables,0,0,1,4,&image,{});});
    if(selectTileVariant(cache,tables,0,0,1,4,nullptr,{})!=0)throw std::runtime_error("Missing image differs");
    cache.initialized=0;refused([&]{selectTileVariant(cache,tables,0,0,0,4,nullptr,{});});
    tables.neighbors[0][0]=2;refused([&]{selectTileVariant(cache,tables,0,0,0,4,nullptr,[]{return 0;});});
    std::cout<<"Tile variant and RNG native domain guards: PASS\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
