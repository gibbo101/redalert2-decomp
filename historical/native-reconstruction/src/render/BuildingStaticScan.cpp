// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/BuildingStaticScan.hpp"
#include "render/UnitVisibility.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
namespace {int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}}
void scanStaticBuildings(const PixelRect& dirty,const PixelRect& clip,std::int32_t force,
        const std::function<PixelPoint()>& offset,const std::function<std::uint8_t()>& bypass,
        const BuildingStaticRegistry& registry){
    const auto requested=intersectDrawBounds(dirty,clip);
    if(!registry.count)throw std::invalid_argument("Building static count unbound");
    if(registry.count()<=0)return;
    std::int32_t index=0;
    do{
        if(!registry.at)throw std::invalid_argument("Building static backing unbound");
        auto a=registry.at(index);
        if(!a.frame.type2c)throw std::invalid_argument("Building static RTTI unbound");
        if(a.frame.type2c()==6){
            bool visible=true;
            if(a.hidden5b7){if(!bypass)throw std::invalid_argument("Building static bypass unbound");visible=bypass()!=0;}
            if(visible){
                if(!offset||!a.frame.bounds124)throw std::invalid_argument("Building static bounds/offset unbound");
                const auto screen=offset();const auto& bounds=a.frame.bounds124();
                const auto x=add(bounds.x,screen.x),y=add(bounds.y,screen.y);
                if(x<add(requested.x,requested.width)&&y<add(requested.y,requested.height)&&
                        add(x,bounds.width)>requested.x&&add(y,bounds.height)>requested.y){
                    if(!a.drawFc)throw std::invalid_argument("Building static drawing child unbound");
                    a.drawFc(clip,force,0);a.frame.redraw75=0;if(a.frame.cleared)a.frame.cleared();
                }
            }
        }
        index=add(index,1);
    }while(index<registry.count());
}
}
