// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/StaticRedraw.hpp"
#include "render/SurfaceFill.hpp"
namespace ra2 {
// Borrowed live owners. The Cell count is reread after every scan. Dirty count
// is saved once, but each reverse step resolves the current backing again.
struct BuildingRedrawRequestServices {
    std::function<std::int32_t()> cellCount,dirtyCount;
    std::function<TerrainCellPoint(std::int32_t)> cellAt;
    std::function<PixelRect(std::int32_t)> dirtyAt;
    std::function<PixelPoint(Coord)> project6a27a0;
    StaticRedrawScan scan6a9f60;
};
// Complete6A4100 with explicit projection/scan children; no queue reset or frame
// schedule. Rectangles/collections must remain alive for the synchronous call.
inline void requestBuildingRedraw(const std::int32_t& originX,const std::int32_t& originY,
        const PixelRect& viewport,const PixelRect& first,const PixelRect& second,
        std::int32_t full,const BuildingRedrawRequestServices& s){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Building redraw request child unbound");return f;};
    const auto cellCount=[&]{const auto n=need(s.cellCount)();if(n>800)throw std::invalid_argument("Building redraw Cell count exceeds backing");return n;};
    for(std::int32_t i=0,n=cellCount();i<n;n=cellCount()){
        const auto p=need(s.cellAt)(i);
        // Signed divide after half-Cell addition is not equivalent to p*256
        // for negative words. Preserve the original41B630 zero Z argument.
        const Coord world{((int(p.x)*256+128)/256)*256,((int(p.y)*256+128)/256)*256,0};
        const auto point=need(s.project6a27a0)(world);
        const auto y=originY,x=originX,viewportY=viewport.y;
        const PixelRect bounds{fillSub(fillSub(point.x,x),30),fillAdd(fillSub(point.y,y),viewportY),60,30};
        const auto clip=bounds;need(s.scan6a9f60)(1,bounds,clip);++i;
    }
    const auto count=need(s.dirtyCount)();
    if(count>128||count==INT32_MIN)throw std::invalid_argument("Building redraw dirty count exceeds backing");
    for(std::int32_t i=count-1;count>0&&i>=0;--i){
        auto r=need(s.dirtyAt)(i);r.y=fillAdd(r.y,viewport.y);
        const auto clipped=intersectFillRect({viewport.x,viewport.y,viewport.width,viewport.height},{r.x,r.y,r.width,r.height});
        if(clipped[2]<=0||clipped[3]<=0)continue;
        const PixelRect bounds{clipped[0],clipped[1],clipped[2],clipped[3]};
        const auto clip=bounds;need(s.scan6a9f60)(1,bounds,clip);
    }
    if(std::uint8_t(full))need(s.scan6a9f60)(1,viewport,viewport);
    else{
        if(first.width>0&&first.height>0)need(s.scan6a9f60)(1,first,first);
        if(second.width>0&&second.height>0)need(s.scan6a9f60)(1,second,second);
    }
}
}
