// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellAttributes.hpp"
#include <bit>
#include <limits>
#include <stdexcept>
namespace ra2 {
namespace {
int s32(std::uint32_t x){return std::bit_cast<std::int32_t>(x);}
MapInputPosition offset(MapInputPosition p,int x,int y){
    return {std::bit_cast<std::int16_t>(std::uint16_t(int(p.x)+x)),
            std::bit_cast<std::int16_t>(std::uint16_t(int(p.y)+y))};
}
bool resident(const MapTileImageInput* image,int sub){
    if(!image)return false;
    const auto count=std::int64_t(image->columns)*image->rows;
    if(image->columns<=0||image->rows<=0||count>std::numeric_limits<int>::max()||
       std::uint64_t(count)!=image->subTiles.size())throw std::invalid_argument("Unsupported resident TMP geometry");
    return sub>=0&&sub<count&&bool(image->subTiles[std::size_t(sub)]);
}
}
int mapAttributeBufferIndex(MapInputPosition p,int a,int b,int count){
    if(count<=0)throw std::invalid_argument("Nonpositive map-buffer capacity");
    const auto width=std::uint32_t(a)+std::uint32_t(b)+1u;
    const int index=s32(width*std::uint32_t(int(p.y))+std::uint32_t(int(p.x)));
    return index<0?0:index>=count?count-1:index;
}
void recalculateMapCellAttributes(MapCellAttributes& c,int level,
    std::span<std::uint8_t,4> b4,std::span<std::uint8_t,10> b10,const MapAttributeServices& s){
    if(s.fallback)return;
    const MapOverlayType* overlay=nullptr;
    if(c.overlay!=-1){
        if(c.overlay<0||std::size_t(c.overlay)>=s.overlays.size())throw std::invalid_argument("Missing map overlay type binding");
        overlay=&s.overlays[std::size_t(c.overlay)];
    }
    if(s.tiles.size()>std::size_t(std::numeric_limits<int>::max()))throw std::invalid_argument("Map tile registry too large");
    auto& v=c.input;
    const auto emit=[&](MapAttributeField f,std::uint32_t n){if(s.store)s.store(f,n);};
    const auto tileStore=[&](int n){v.tile=n;emit(MapAttributeField::Tile,std::uint32_t(n));};
    const auto landStore=[&](int n){v.land=n;emit(MapAttributeField::Land,std::uint32_t(n));};
    const auto slopeStore=[&](std::uint8_t n){v.slope=n;emit(MapAttributeField::Slope,n);};
    const auto clearOverlay=[&]{c.overlay=-1;emit(MapAttributeField::Overlay,0xffffffffu);c.overlayData=0;emit(MapAttributeField::OverlayData,0);};
    const auto nearCliff=[&]{
        if(!s.cliffMode)return false;
        if(!s.neighborLevel)throw std::invalid_argument("Missing map cliff neighbor service");
        for(const auto d:std::array<MapInputPosition,6>{{{0,-1},{-1,0},{2,2},{1,1},{-1,1},{1,-1}}})
            if(int(v.level)+4<=s.neighborLevel(offset(v.position,d.x,d.y)))return true;
        return false;
    };
    const auto finish=[&](bool invalidImage){
        if(nearCliff()&&s.cliffMode==2&&(v.land==0||(!invalidImage&&(v.land==2||v.land==6||v.land==8))))landStore(3);
        if(!s.updatePassability)throw std::invalid_argument("Missing Cell passability service");
        c.passability=s.updatePassability(c);
        b4[1]=std::uint8_t(v.level);emit(MapAttributeField::Buffer4,0x100u|b4[1]);
        // The invalid-image early return writes the ten-byte record first.
        if(invalidImage){b10[8]=std::uint8_t(v.level);emit(MapAttributeField::Buffer10,0x800u|b10[8]);}
        b4[0]=std::uint8_t(c.passability);emit(MapAttributeField::Buffer4,b4[0]);
        if(!invalidImage){b10[8]=std::uint8_t(v.level);emit(MapAttributeField::Buffer10,0x800u|b10[8]);}
    };
    if(overlay){
        landStore(overlay->land);
        if(overlay->land==4||overlay->land==9||overlay->noUseTileLandType){
            if(v.tile!=65535&&v.tile<int(s.tiles.size())){
                if(v.tile<0)throw std::invalid_argument("Negative map tile registry subscript");
                slopeStore(std::uint8_t(mapTileRamp(s.tiles[std::size_t(v.tile)].image,v.subTile)));
            }
            if(v.slope&&overlay->tiberium)clearOverlay();
            if(nearCliff()&&s.cliffMode==2)landStore(3);
            if(!s.setupLAT||!s.updatePassability)throw std::invalid_argument("Missing overlay Cell child service");
            v.tile=s.setupLAT(c);c.passability=s.updatePassability(c);
            b4[1]=std::uint8_t(v.level);emit(MapAttributeField::Buffer4,0x100u|b4[1]);
            b10[8]=std::uint8_t(v.level);emit(MapAttributeField::Buffer10,0x800u|b10[8]);
            b4[0]=std::uint8_t(c.passability);emit(MapAttributeField::Buffer4,b4[0]);
            return;
        }
    }
    if(v.tile>=int(s.tiles.size()))tileStore(65535);
    if(v.tile==65535){landStore(overlay?overlay->land:0);slopeStore(0);finish(false);return;}
    if(v.tile<0)throw std::invalid_argument("Negative map tile registry subscript");
    const auto& tile=s.tiles[std::size_t(v.tile)];
    if(!resident(tile.image,v.subTile)){
        tileStore(65535);v.subTile=0;emit(MapAttributeField::SubTile,0);landStore(0);slopeStore(0);finish(true);return;
    }
    // Refuse unsupported allocation/neighbor-write branches. For overlays the
    // actual resulting land is known only after classification below.
    if(!(v.flags&0x20000u)&&tile.animation!=-1&&tile.animationSubTile==v.subTile)
        throw std::invalid_argument("Map tile animation construction is unrecovered");
    if(tile.shadowCaster)throw std::invalid_argument("Shadow-casting map neighbor writes are unrecovered");
    slopeStore(std::uint8_t(mapTileRamp(tile.image,v.subTile)));
    if(!s.setupLAT)throw std::invalid_argument("Missing Cell LAT service");
    v.tile=s.setupLAT(c);
    if(overlay){
        if(!s.classifyResource)throw std::invalid_argument("Missing map resource classifier");
        if(s.classifyResource(c.overlay)!=-1){
            if(v.slope>4){landStore(mapTileLand(tile.image,v.subTile,s.landMap));clearOverlay();}
            else if(overlay->land==0)landStore(5);
        }else if(!overlay->noUseTileLandType)landStore(mapTileLand(tile.image,v.subTile,s.landMap));
    }else landStore(mapTileLand(tile.image,v.subTile,s.landMap));
    if(v.land==10&&(v.tube<0||int(v.tube)>=s.tubeCount))throw std::invalid_argument("New map tube construction is unrecovered");
    if(level!=-1){v.level=std::bit_cast<std::int8_t>(std::uint8_t(level));emit(MapAttributeField::Level,std::uint8_t(v.level));}
    int w=0,h=0;mapTileDimensions(tile.image,v.subTile,w,h);
    c.extraHeight=std::uint8_t(s32(std::uint32_t(h)-30u)/15);emit(MapAttributeField::ExtraHeight,c.extraHeight);
    finish(false);
}
}
