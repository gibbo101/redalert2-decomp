// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingVisibility.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
int sub(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
}
bool drawBuildingIfVisible(BuildingVisibilityFields a,PixelRect& clip,const PixelRect& viewport,
        std::int32_t force,std::int32_t special,const BuildingVisibilityServices& s){
    const auto read=[&](int off,const std::uint8_t& v){const auto result=v;if(s.read)s.read(off,result);return result;};
    const auto store=[&](int off,int& field,int v){field=v;if(s.store)s.store(off,v);};
    if(!s.bypass)throw std::invalid_argument("Building visibility bypass unbound");
    if(!s.bypass()){
        if(!s.contextPresent)throw std::invalid_argument("Building visibility context unbound");
        if(s.contextPresent()){
            if(!std::uint8_t(force)&&!read(0x75,a.redraw75))return false;
            if(!read(0x74,a.marked74)||read(0x76,a.flag76))return false;
        }
    }
    a.redraw75=0;if(s.store)s.store(0x75,0);
    const auto clipped=intersectDrawBounds(clip,viewport);
    store(0,clip.x,clipped.x);store(4,clip.y,clipped.y);store(8,clip.width,clipped.width);store(12,clip.height,clipped.height);
    const auto offset=PixelPoint{viewport.x,viewport.y};
    if(!s.bounds124)throw std::invalid_argument("Building visibility bounds unbound");
    const auto bounds=s.bounds124();const auto x=add(bounds.x,offset.x),y=add(bounds.y,offset.y);
    if(clip.x>=add(x,bounds.width)||clip.y>=add(y,bounds.height)||add(clip.x,clip.width)<=x||add(clip.y,clip.height)<=y)return false;
    if(!s.coordinatesA8||!s.project6a29d0)throw std::invalid_argument("Building visibility coordinate/projection unbound");
    auto point=s.project6a29d0(s.coordinatesA8());
    if(clip.x>viewport.x){point.x=add(point.x,sub(viewport.x,clip.x));if(s.store)s.store(16,point.x);}
    if(clip.y>viewport.y){point.y=add(point.y,sub(viewport.y,clip.y));if(s.store)s.store(20,point.y);}
    if(std::uint8_t(special)){
        if(!read(0x5b7,a.hidden5b7)){
            if(!s.special470)throw std::invalid_argument("Building special drawing unbound");
            s.special470(point,clip);
        }
    }else{
        if(!s.ordinary10c)throw std::invalid_argument("Building ordinary drawing unbound");
        s.ordinary10c(point,clip);
    }
    return true;
}
}
