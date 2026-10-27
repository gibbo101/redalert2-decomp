// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellInputs.hpp"
#include <array>
#include <stdexcept>
using namespace ra2;
template<class F>void refused(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("Unsafe map input accepted");}
int main(){
    MapCellInput fallback;fallback.flags=0x12345678;std::vector<MapCellInput*> table(262144);
    refused([&]{loadIsoMapCellInputs({},std::span<MapCellInput* const>(table.data(),3),fallback,{},{});});
    if(fallback.flags!=0x12345678)throw std::runtime_error("Table-size guard changed fallback");
    refused([&]{loadIsoMapCellInputs({},table,fallback,{},{});});
    MapTileImageInput image;int w=17,h=-9;
    refused([&]{mapTileDimensions(&image,0,w,h);});
    image.columns=1;image.rows=1;image.subTiles={MapSubTileInput{}};
    refused([&]{mapTileRamp(&image,-1);});
    image.subTiles[0]->land=255;
    refused([&]{mapTileLand(&image,0,std::array<int,16>{});});
    image.subTiles[0]->land=15;
    refused([&]{mapTileLand(&image,0,std::array<int,1>{});});
    image.columns=2147483647;image.rows=2147483647;
    refused([&]{mapTileDimensions(&image,0,w,h);});
}
