// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellAttributes.hpp"
#include <stdexcept>
using namespace ra2;
template<class F>void refused(F f){bool caught=false;try{f();}catch(const std::invalid_argument&){caught=true;}if(!caught)throw std::runtime_error("Unrecovered map attribute domain accepted");}
int main(){
    std::array<std::uint8_t,4>b4{};std::array<std::uint8_t,10>b10{};
    MapCellAttributes c;MapAttributeServices s;s.fallback=true;
    recalculateMapCellAttributes(c,-1,b4,b10,s);
    s.fallback=false;c.overlay=0;
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,s);});
    c.overlay=-1;c.input.tile=-1;
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,s);});
    refused([&]{mapAttributeBufferIndex({},1,1,0);});
    MapTileImageInput image;image.columns=image.rows=1;image.subTiles={MapSubTileInput{}};
    std::array<MapTileAttributes,1> tiles{};tiles[0].image=&image;s.tiles=tiles;
    std::array<int,16> mapping{};s.landMap=mapping;c.input.tile=0;
    tiles[0].animation=0;
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,s);});
    if(c.input.tile!=0||c.input.slope!=0)throw std::runtime_error("Animation guard altered Cell fields");
    tiles[0].animation=-1;tiles[0].shadowCaster=true;
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,s);});
    tiles[0].shadowCaster=false;mapping[0]=10;
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,s);});
    mapping[0]=0;image.columns=0;
    refused([&]{recalculateMapCellAttributes(c,-1,b4,b10,s);});
}
