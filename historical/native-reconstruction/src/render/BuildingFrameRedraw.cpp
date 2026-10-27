// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingFrameRedraw.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <stdexcept>

namespace ra2 {
namespace {
std::int32_t add(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
std::int32_t sub(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
std::int32_t mul(std::int32_t a,std::uint32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)*b);}
std::int32_t lowFTOL(double v){
    return !std::isfinite(v)||v<-0x1p63||v>=0x1p63?0:
        std::bit_cast<std::int32_t>(std::uint32_t(std::int64_t(v)));
}
}
PixelPoint projectTacticalPlanar(PixelPoint p){
    return {add(mul(p.x,60)/2,mul(p.y,std::uint32_t(-60))/2)/256,
        add(mul(p.x,30)/2,mul(p.y,30)/2)/256};
}
PixelPoint frameWorldPosition(Coord p,double scale){
    if(!std::isfinite(scale)||scale<=0||scale>1)throw std::invalid_argument("Frame height scale outside tested domain");
    OriginalRounding rounding;
    const auto planar=projectTacticalPlanar({p.x,p.y});
    const auto height=lowFTOL((double(p.z)*scale+(p.z>=728?1:0))+0.5);
    return {planar.x,sub(planar.y,height)};
}
bool projectTacticalFrame(Coord p,PixelPoint& out,double scale,const std::int32_t& width,
        const std::int32_t& height,const TacticalProjectionServices& services){
    const auto world=frameWorldPosition(p,scale);
    const auto store=[&](int offset,int& field,int value){field=value;if(services.store)services.store(offset,value);};
    store(0,out.x,world.x);store(4,out.y,world.y);
    if(!services.origin)throw std::invalid_argument("Tactical frame origin unbound");
    const auto origin=services.origin();
    store(0,out.x,sub(out.x,origin.x));store(4,out.y,sub(out.y,origin.y));
    return out.x>=-360&&out.x<=add(width,360)&&out.y>=-180&&out.y<=add(height,180);
}
bool buildingRedrawInFrame(PixelPoint origin,PixelRect viewport,double scale,const BuildingFrameRegistry& registry){
    if(!registry.count)throw std::invalid_argument("Building frame count unbound");
    if(!std::isfinite(scale)||scale<=0||scale>1)throw std::invalid_argument("Building frame height scale outside tested domain");
    OriginalRounding rounding;
    const auto left=add(origin.x,viewport.x),top=add(origin.y,viewport.y);
    const auto right=add(add(origin.x,viewport.width),viewport.x);
    const auto bottom=add(add(origin.y,viewport.height),viewport.y);
    if(registry.count()<=0)return false;
    std::int32_t index=0;
    do {
        if(!registry.at)throw std::invalid_argument("Building frame backing unbound");
        const auto a=registry.at(index);
        const auto read=[&](int offset,const std::uint8_t& value){const auto v=value;if(a.read)a.read(offset,v);return v;};
        if(read(0x7d,a.onMap7d)&&read(0x75,a.redraw75)&&read(0x74,a.marked74)){
            if(!a.coordinatesA8)throw std::invalid_argument("Building frame coordinate child unbound");
            const auto p=a.coordinatesA8();
            const auto projected=frameWorldPosition(p,scale);
            if(projected.x>=left&&projected.x<=right&&projected.y>=top&&projected.y<=bottom)return true;
        }
        index=add(index,1);
    }while(index<registry.count());
    return false;
}
}
