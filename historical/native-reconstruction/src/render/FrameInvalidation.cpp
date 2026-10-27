// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/FrameInvalidation.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}}
void invalidateFrameBuildings(PixelRect r,const PixelPoint& offset,const FrameInvalidationRegistry& registry,
        const std::function<void(PixelRect,std::uint8_t)>& registerDirty){
    if(!registry.count)throw std::invalid_argument("Frame invalidation count unbound");
    if(registry.count()<=0)return;
    std::int32_t index=0;
    do {
        if(!registry.at)throw std::invalid_argument("Frame invalidation backing unbound");
        const auto a=registry.at(index);
        if(!a.type2c)throw std::invalid_argument("Frame invalidation type child unbound");
        if(a.type2c()==6&&a.redraw75){
            if(!a.bounds124)throw std::invalid_argument("Frame invalidation bounds child unbound");
            const auto& bounds=a.bounds124();
            const auto x=add(bounds.x,offset.x),y=add(bounds.y,offset.y);
            if(r.x<add(x,bounds.width)&&r.y<add(y,bounds.height)&&add(r.x,r.width)>x&&add(r.y,r.height)>y){
                if(!registerDirty)throw std::invalid_argument("Frame invalidation registration child unbound");
                registerDirty(bounds,0);a.redraw75=0;if(a.cleared)a.cleared();
            }
        }
        index=add(index,1);
    }while(index<registry.count());
}
}
