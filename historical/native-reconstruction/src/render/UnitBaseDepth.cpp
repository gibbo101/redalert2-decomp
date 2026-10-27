// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/UnitBaseDepth.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));}
MapInputPosition coordinates(Coord p){return {std::bit_cast<std::int16_t>(std::uint16_t(p.x/256)),std::bit_cast<std::int16_t>(std::uint16_t(p.y/256))};}
MapInputPosition neighbor(MapInputPosition p,int direction){
    const auto [x,y]=directionOffset(direction&7);
    return {std::bit_cast<std::int16_t>(std::uint16_t(int(p.x)+x)),std::bit_cast<std::int16_t>(std::uint16_t(int(p.y)+y))};
}
int pixels(double scale,int height){
    // Signed threshold, 53-bit arithmetic and qword FTOL/low-dword return.
    const double result=(double(height)*scale+double(height>=728))+0.5;
    return signed32(std::uint32_t(std::int64_t(result)));
}
}
UnitBaseDepthResult ordinaryUnitBaseDepth(const UnitBaseDepthInputs& in,const UnitBaseDepthWorld& w){
    if(!w.cell||!std::isfinite(in.heightScale)||in.heightScale<=0||in.heightScale>1)
        throw std::invalid_argument("Unsupported ordinary Unit base-depth binding");
    OriginalRounding rounding;
    const auto query=[&](int kind){if(w.query)w.query(kind);};
    query(0);const int base=signed32(0u-std::uint32_t(pixels(in.heightScale,in.location.z)));
    query(1);const auto position=coordinates(in.location);const auto& current=w.cell(position);
    const auto result=[&](int delta,int scratch){return UnitBaseDepthResult{add(base,delta),scratch};};
    if(current.input.slope){
        const auto& south=w.cell(neighbor(position,4));const auto& east=w.cell(neighbor(position,2));const auto& diagonal=w.cell(neighbor(position,3));
        for(const auto* cell:{&south,&east,&diagonal}){
            if(cell->overlay==-1)continue;
            if(cell->overlay<0||std::size_t(cell->overlay)>=w.overlays.size())throw std::invalid_argument("Missing base-depth overlay binding");
            if(w.overlays[std::size_t(cell->overlay)].rock)return result(add(in.rock,-1),in.dimensionHeight);
            break; // First occupied overlay gates later candidates, even if not rock.
        }
    }
    const auto heading=[&]{query(2);return ((unsigned(in.facing.current(in.tick))>>12)+1u)>>1;};
    std::array<const MapCellAttributes*,6> cells;
    const int offsets[]={1,-1,0,-4,3,-3};
    for(std::size_t i=0;i<cells.size();++i)cells[i]=&w.cell(neighbor(position,int(heading())+offsets[i]));
    for(const auto* cell:cells)if(cell->input.slope)return result(in.neighborRamp,in.dimensionHeight);
    if(current.input.slope)return result(in.currentRamp,in.dimensionHeight);
    unsigned selected=0;
    if((heading()&7u)==6u)selected=3;
    else if((heading()&7u)==0u)selected=3;
    else if((heading()&7u)==4u)selected=0;
    else if((heading()&7u)!=2u)return result(-1,in.dimensionHeight);
    if(current.input.flags&0x10000u)return result(-1,in.dimensionHeight);
    for(unsigned i=0;i<3;++i)if(cells[selected+i]->input.flags&0x10000u)return result(-1,in.dimensionHeight);
    int scratch=in.dimensionHeight;
    for(unsigned i=0;i<3;++i){
        const auto& cell=cells[selected+i]->input;
        const bool sentinel=cell.tile==65535||cell.tile==255;
        const int tile=sentinel?in.defaultTile:cell.tile,sub=sentinel?0:cell.subTile;
        if(tile<0||std::size_t(tile)>=w.tiles.size())throw std::invalid_argument("Missing base-depth tile binding");
        if(w.dimensions)w.dimensions(tile,sub);
        int width=0;mapTileDimensions(w.tiles[std::size_t(tile)].image,sub,width,scratch);
        if(scratch>36)return result(-2,scratch);
    }
    return result(-1,scratch);
}
}
