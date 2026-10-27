// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/FrameRegionPreparation.hpp"
namespace ra2 {
struct FrameTerrainServices {
    std::function<std::int32_t()> cellCount,dirtyCount;
    std::function<int(int)> cellAt;
    std::function<Coord(int)> center475d60;
    std::function<PixelPoint(Coord)> project6a27a0;
    std::function<std::span<DirtyRegion>()> dirtyBacking;
    std::function<void(int,std::uint8_t)> dirtyFlagTrace;
    std::function<bool()> terrainPresent;
    std::function<void(int,PixelPoint,const PixelRect&)> terrain475520;
    std::function<void(PixelPoint,const PixelRect&)> animation41f1c0;
    std::function<void(const PixelRect&)> rectangle6a7820,alpha4110b0;
};
// Complete6A3EF0 with borrowed live queues and explicit child effects. The
// entered terrain/animation draw children are separate dependencies. No reset.
inline void requestFrameTerrain(const std::int32_t& originX,const std::int32_t& originY,
        const PixelRect& viewport,const PixelRect& first,const PixelRect& second,
        const PixelRect& clip,std::int32_t full,const FrameTerrainServices& s){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Frame terrain child unbound");return f;};
    const auto cells=[&]{const auto n=need(s.cellCount)();if(n>800)throw std::invalid_argument("Frame terrain Cell count exceeds backing");return n;};
    const auto count=cells();
    if(std::uint8_t(full))need(s.rectangle6a7820)(viewport);
    else if(count>0){
        for(int i=0,n=count;i<n;){
            auto world=need(s.center475d60)(need(s.cellAt)(i));world.z=0;
            const auto p=need(s.project6a27a0)(world);
            const auto x=originX,y=originY;
            const PixelPoint screen{fillSub(fillAdd(fillSub(p.x,x),viewport.x),30),
                fillSub(fillAdd(fillSub(p.y,y),viewport.y),15)};
            // The draw path reloads this slot after center/projection queries.
            if(need(s.terrainPresent)())need(s.terrain475520)(need(s.cellAt)(i),screen,clip);
            need(s.animation41f1c0)(screen,clip);
            n=cells();++i;
        }
    }
    if(!std::uint8_t(full)){
        if(first.width>0&&first.height>0)need(s.rectangle6a7820)(first);
        if(second.width>0&&second.height>0)need(s.rectangle6a7820)(second);
    }
    const auto dirty=[&]{auto n=need(s.dirtyCount)();if(n>128)throw std::invalid_argument("Frame terrain dirty count exceeds backing");return n;};
    // Forward traversal rereads live count and backing. Unlike several sibling
    // passes, dirty entries remain eligible even when the full low byte is set.
    const auto at=[](std::span<DirtyRegion> rows,int i)->DirtyRegion&{
        if(i<0||std::size_t(i)>=rows.size())throw std::invalid_argument("Frame terrain dirty slot exceeds backing");return rows[i];};
    auto n=dirty();if(n<=0)return;
    auto rows=need(s.dirtyBacking)();
    for(int i=0;i<n;){
        auto r=at(rows,i).bounds;
        r.x=fillAdd(r.x,viewport.x);r.y=fillAdd(r.y,viewport.y);
        // Original EDx is the translated region; the caller clip is its
        // second operand. Wrapped clipping is not commutative.
        const auto c=intersectFillRect({r.x,r.y,r.width,r.height},{clip.x,clip.y,clip.width,clip.height});
        const PixelRect clipped{c[0],c[1],c[2],c[3]};
        // The flag is a late load after intersection. Even an empty result is
        // forwarded when flagged; no invented positive-size filter is applied.
        rows=need(s.dirtyBacking)();
        const auto flag=at(rows,i).flag;if(s.dirtyFlagTrace)s.dirtyFlagTrace(i,flag);
        if(flag){
            need(s.alpha4110b0)(clipped);
            need(s.rectangle6a7820)(clipped);
            rows=need(s.dirtyBacking)(); // Retain this pointer into the next iteration.
        }
        n=dirty();++i;
    }
}
}
