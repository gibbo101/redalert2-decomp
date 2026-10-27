// SPDX-License-Identifier: GPL-3.0-or-later
#include "render/StaticTerrainTraversal.hpp"
#include <bit>
namespace ra2 {
namespace {
int add(int a,int b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
}
void drawStaticTerrainRegion(std::span<const int> layer,std::uint8_t force,
                             PixelRect dirty,PixelRect clip,PixelRect viewport,
                             const StaticTerrainTraversalServices& services){
    const auto intersection=intersectDrawBounds(dirty,clip);
    for(auto slot=layer.rbegin();slot!=layer.rend();++slot){
        const int id=*slot;
        if(!services.isTerrain(id)||services.isDead(id)||services.isAnimated(id)||services.isCrumbling(id))continue;
        const auto shape=services.renderBounds(id);
        const int x=add(shape.x,viewport.x),y=add(shape.y,viewport.y);
        if(x>=add(intersection.x,intersection.width)||y>=add(intersection.y,intersection.height)||
           add(x,shape.width)<=intersection.x||add(y,shape.height)<=intersection.y)continue;
        auto bounds=clip; // Each actor receives the unmodified third argument.
        services.drawIfVisible(id,bounds,force);
        services.clearRedraw(id); // Also performed after a rejected eligibility call.
    }
}
}
