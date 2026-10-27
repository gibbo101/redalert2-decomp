// SPDX-License-Identifier: GPL-3.0-or-later
#include "assets/MapFloorHeight.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <limits>
#include <stdexcept>
namespace ra2 {
namespace {
int truncateDword(double n) {
    if(!(n>=-9223372036854775808.0&&n<9223372036854775808.0))
        throw std::invalid_argument("Floor height outside finite qword domain");
    return signed32(std::uint32_t(std::int64_t(n)));
}
void initialize(MapFloorHeightState& s,int current) {
    if(!(s.flags&1)){s.flags|=1;s.height=double(current);}
    if(!(s.flags&2)){s.flags|=2;s.scale=s.height/256.0;}
    if(s.flags&4)return;
    s.flags|=4;const double h=s.height,twice=h+h,half=h*0.5;
    // The first plane's direction/offset belong to the supplied static template.
    s.planes[0].limit=h;s.planes[0].add=0;
    s.planes[1]={0,1,0,h,0};s.planes[2]={-1,0,h,h,0};s.planes[3]={0,-1,h,h,0};
    for(int direction=0;direction<4;++direction) {
        const double x=direction==0||direction==3?1:-1,y=direction<2?1:-1;
        const int negatives=int(x<0)+int(y<0);
        const double corner=negatives?double(negatives)*h:0;
        const double lower=negatives==0?-h:negatives==1?0:h;
        s.planes[std::size_t(4+direction)]={x,y,lower,h,0};
        s.planes[std::size_t(8+direction)]={x,y,corner,h,0};
        s.planes[std::size_t(12+direction)]={x,y,corner,twice,0};
        s.planes[std::size_t(16+direction)]={0,0,direction%2?h:0,half,direction%2?-half:half};
    }
}
void validate(const MapFloorHeightState& s,std::uint8_t ramp) {
    if(ramp>20||!std::isfinite(s.height)||!std::isfinite(s.scale))
        throw std::invalid_argument("Unsupported floor height state/ramp");
    for(const auto& p:s.planes)
        for(double v:{p.x,p.y,p.offset,p.limit,p.add})
            if(!std::isfinite(v))throw std::invalid_argument("Nonfinite floor plane");
}
}
int cellFloorHeight(MapFloorHeightState& s,int current,std::int8_t level,
    std::uint8_t ramp,int x,int y) {
    validate(s,ramp);OriginalRounding rounding;initialize(s,current);
    const int product=signed32(std::uint32_t(int(level))*std::uint32_t(current));
    const int base=truncateDword(double(product)+0.5);
    if(!ramp)return base;
    const auto& p=s.planes[std::size_t(ramp-1)];
    const double yy=(double(std::uint32_t(y)&255)*p.y)*s.scale;
    const double xx=(double(std::uint32_t(x)&255)*p.x)*s.scale;
    double delta=((xx+yy)+p.offset)+p.add;
    if(delta<0)delta=0;
    if(delta>p.limit)delta=p.limit;
    return truncateDword(double(base)+delta);
}
int mapFloorHeight(MapFloorHeightState& s,int current,Coord point,const MapFloorHeightWorld& w) {
    if(w.cells.size()>262144||!w.fallback)throw std::invalid_argument("Unsupported floor map binding");
    const int x=point.x/256,y=point.y/256;
    const int index=signed32((std::uint32_t(y)<<9)+std::uint32_t(x));
    auto* cell=index>=0&&std::size_t(index)<w.cells.size()?w.cells[std::size_t(index)]:nullptr;
    if(!cell) {
        cell=w.fallback;
        cell->position={std::bit_cast<std::int16_t>(std::uint16_t(x)),std::bit_cast<std::int16_t>(std::uint16_t(y))};
        if(w.fallbackStore)w.fallbackStore(cell->position);
    }
    return cellFloorHeight(s,current,cell->level,cell->slope,point.x,point.y);
}
int relativeMapHeight(MapFloorHeightState& s,int current,Coord point,
    std::uint8_t bridge,int bridgeHeight,const MapFloorHeightWorld& w) {
    int result=signed32(std::uint32_t(point.z)-std::uint32_t(mapFloorHeight(s,current,point,w)));
    if(bridge)result=signed32(std::uint32_t(result)-std::uint32_t(bridgeHeight));
    return result;
}
Coord mapCellCenterHeight(MapFloorHeightState& s,int current,const MapCellInput& cell) {
    Coord point{int(cell.position.x)*256+128,int(cell.position.y)*256+128,0};
    point.z=cellFloorHeight(s,current,cell.level,cell.slope,point.x,point.y);return point;
}
}
