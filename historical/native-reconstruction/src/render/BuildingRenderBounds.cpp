// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingRenderBounds.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
const PixelRect& buildingRenderBounds(BuildingRenderBoundsState& a,const BuildingRenderBoundsServices& s){
    if(!s.coordinatesA8||!s.origin)throw std::invalid_argument("Building render-bound coordinate/origin child unbound");
    const auto p=s.coordinatesA8(),saved=a.coordinates51c;
    const auto origin=s.origin();
    if(p==saved&&origin==a.origin528)return a.bounds50c;
    if(!s.project6a29d0||!s.typeBounds45e290)throw std::invalid_argument("Building render-bound projection/type child unbound");
    const auto at=s.project6a29d0(p);
    const auto type=s.typeBounds45e290();
    const auto add=[](int x,int y){return std::bit_cast<std::int32_t>(std::uint32_t(x)+std::uint32_t(y));};
    const auto store=[&](int offset,int& field,int value){field=value;if(s.store)s.store(offset,value);};
    store(0x51c,a.coordinates51c.x,p.x);store(0x520,a.coordinates51c.y,p.y);store(0x524,a.coordinates51c.z,p.z);
    store(0x528,a.origin528.x,origin.x);store(0x52c,a.origin528.y,origin.y);
    store(0x50c,a.bounds50c.x,add(type.x,at.x));store(0x510,a.bounds50c.y,add(type.y,at.y));
    store(0x514,a.bounds50c.width,type.width);store(0x518,a.bounds50c.height,type.height);
    return a.bounds50c;
}
}
