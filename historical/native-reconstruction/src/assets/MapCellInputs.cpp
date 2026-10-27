// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapCellInputs.hpp"
#include <bit>
#include <limits>
#include <stdexcept>
namespace ra2 {
namespace {
int signed32(std::uint32_t x){return std::bit_cast<std::int32_t>(x);}
std::uint32_t packed(MapInputPosition p){return std::uint16_t(p.x)|(std::uint32_t(std::uint16_t(p.y))<<16);}
void changed(const MapInputStore& s,MapCellInput& c,MapInputField f,std::uint32_t v){if(s)s(&c,f,v);}
const MapSubTileInput* sample(const MapTileImageInput& image,int sub){
    const auto count=std::int64_t(image.columns)*image.rows;
    if(sub<0||image.columns<=0||image.rows<=0||count>std::numeric_limits<int>::max()||
       std::uint64_t(count)!=image.subTiles.size())throw std::invalid_argument("Unsupported resident TMP geometry/subscript");
    const auto& value=image.subTiles[std::size_t(sub%int(count))];return value?&*value:nullptr;
}
}
void resetMapCellInput(MapCellInput& c,MapInputPosition invalid,const MapInputStore& s){
    c.position=invalid;changed(s,c,MapInputField::Position,packed(invalid));
    c.tile=65535;changed(s,c,MapInputField::Tile,65535);
    c.tube=-1;changed(s,c,MapInputField::Tube,65535);
    c.land=0;changed(s,c,MapInputField::Land,0);
    c.ice=0;changed(s,c,MapInputField::Ice,0);
    c.subTile=0;changed(s,c,MapInputField::SubTile,0);
    c.level=0;changed(s,c,MapInputField::Level,0);
    c.slope=0;changed(s,c,MapInputField::Slope,0);
    c.flags&=0xff800000u;changed(s,c,MapInputField::Flags,c.flags);
}
int mapInputTileIndex(int index,std::span<const MapTileShift> shifts){
    if(index==65535)return index;
    auto result=std::uint32_t(index);
    for(const auto shift:shifts){if(shift.first>index)break;result+=std::uint32_t(shift.delta);}
    return signed32(result);
}
std::size_t loadIsoMapCellInputs(std::span<const std::uint8_t> data,std::span<MapCellInput* const> cells,
    MapCellInput& fallback,MapInputPosition terminator,MapInputPosition invalid,
    std::span<const MapTileShift> shifts,const MapInputStore& store){
    if(cells.size()!=262144)throw std::invalid_argument("IsoMap input requires 512*512 pointer table");
    std::size_t offset=0;
    auto read=[&](unsigned n){if(data.size()-offset<n)throw std::invalid_argument("Truncated decoded IsoMap stream");
        std::uint32_t v=0;for(unsigned i=0;i<n;++i)v|=std::uint32_t(data[offset++])<<(i*8);return v;};
    for(;;){
        const auto position=read(4);
        MapInputPosition p{std::bit_cast<std::int16_t>(std::uint16_t(position)),std::bit_cast<std::int16_t>(std::uint16_t(position>>16))};
        if(p==terminator)break;
        const int index=int(p.y)*512+int(p.x);
        auto* cell=index>=0&&index<262144?cells[std::size_t(index)]:nullptr;
        if(!cell){fallback.position=p;changed(store,fallback,MapInputField::Position,position);read(4);read(3);continue;}
        cell->tile=65535;changed(store,*cell,MapInputField::Tile,65535);
        cell->tile=signed32(read(4));changed(store,*cell,MapInputField::Tile,std::uint32_t(cell->tile));
        cell->tile=mapInputTileIndex(cell->tile,shifts);changed(store,*cell,MapInputField::Tile,std::uint32_t(cell->tile));
        cell->subTile=std::uint8_t(read(1));changed(store,*cell,MapInputField::SubTile,cell->subTile);
        cell->level=std::bit_cast<std::int8_t>(std::uint8_t(read(1)));changed(store,*cell,MapInputField::Level,std::uint8_t(cell->level));
        cell->ice=std::uint8_t(read(1));changed(store,*cell,MapInputField::Ice,cell->ice);
    }
    resetMapCellInput(fallback,invalid,store);return offset;
}
int mapTileLand(const MapTileImageInput* image,int sub,std::span<const int> mapping){
    if(!image)return 0;const auto* tile=sample(*image,sub);if(!tile)return 0;
    const int index=std::bit_cast<std::int8_t>(tile->land);
    if(index<0||std::size_t(index)>=mapping.size())throw std::invalid_argument("TMP land byte outside supplied table");
    return mapping[std::size_t(index)];
}
int mapTileRamp(const MapTileImageInput* image,int sub){
    if(!image)return 0;const auto* tile=sample(*image,sub);return tile?std::bit_cast<std::int8_t>(tile->ramp):0;
}
bool mapTileDimensions(const MapTileImageInput* image,int sub,int& w,int& h){
    if(!image)return false;const auto* tile=sample(*image,sub);w=image->width;h=image->height;
    if(tile&&tile->extra)h=signed32(std::uint32_t(tile->y)-std::uint32_t(tile->extraY)+std::uint32_t(h));
    return true;
}
}
