// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/StaticRedraw.hpp"
#include "render/SurfaceFill.hpp"
namespace ra2 {
// Complete6A33F0, with synchronous borrowed queues and explicit entered children.
// This prepares regions; it does not perform the outer frame's queue reset.
struct FrameRegionServices {
    std::function<std::int32_t()> dirtyCount,cellCount;
    std::function<void(std::int32_t)> setDirtyCount;
    std::function<std::span<DirtyRegion>()> dirtyBacking;
    std::function<int(std::int32_t)> cellAt;
    std::function<Coord(int)> center475d60;
    std::function<PixelPoint(Coord)> project6a27a0;
    std::function<bool()> terrainPresent;
    std::function<void(const PixelRect&)> depth7761c0;
    std::function<void(int,PixelPoint,const PixelRect&)> terrain4754b0;
    // Ordered queue writes, including the fifth word on a shifted record. Native
    // representation retains its meaningful flag byte, not original padding.
    std::function<void(int,int,std::int32_t)> storeTrace;
};
inline void prepareFrameRegions(const std::int32_t& originX,const std::int32_t& originY,
        const PixelRect& viewport,std::int32_t full,std::int32_t dx,std::int32_t dy,
        const PixelRect& clip,const FrameRegionServices& s){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Frame region child unbound");return f;};
    const auto dirtyCount=[&]{auto n=need(s.dirtyCount)();if(n>128||n==INT32_MIN)throw std::invalid_argument("Frame region dirty count exceeds backing");return n;};
    const auto backing=[&](int i){auto rows=need(s.dirtyBacking)();if(i<0||std::size_t(i)>=rows.size())throw std::invalid_argument("Frame region dirty slot exceeds backing");return rows;};
    const auto store=[&](DirtyRegion& d,int i,PixelRect r){
        d.bounds.x=r.x;if(s.storeTrace)s.storeTrace(i,0,r.x);
        d.bounds.y=r.y;if(s.storeTrace)s.storeTrace(i,1,r.y);
        d.bounds.width=r.width;if(s.storeTrace)s.storeTrace(i,2,r.width);
        d.bounds.height=r.height;if(s.storeTrace)s.storeTrace(i,3,r.height);
    };
    if(!std::uint8_t(full)){
        const auto count=dirtyCount();
        for(int i=count>0?count-1:-1;i>=0;--i){
            auto r=backing(i)[i].bounds;r.x=fillAdd(r.x,dx);r.y=fillAdd(r.y,dy);
            // Actual47D040 subtracts two copies of the viewport origin;453E40
            // therefore constructs (0,0,width,height), even for nonzero origin.
            const auto c=intersectFillRect({0,0,viewport.width,viewport.height},{r.x,r.y,r.width,r.height});
            r={c[0],c[1],c[2],c[3]};store(backing(i)[i],i,r);
            if(r.width<=0||r.height<=0){
                const auto n=dirtyCount();
                if(i<n){
                    const auto last=n-1;need(s.setDirtyCount)(last);
                    if(i<last){
                        for(int j=i;;){
                            // One backing load per shifted record, including
                            // its flag. Do not clear the unused capacity tail.
                            auto rows=backing(j+1);auto& destination=rows[j];
                            auto& source=rows[j+1];
                            const auto copy=source;store(destination,j,copy.bounds);
                            destination.flag=copy.flag;if(s.storeTrace)s.storeTrace(j,4,copy.flag);
                            ++j;if(j>=dirtyCount())break;
                        }
                    }
                }
            }else need(s.depth7761c0)(r);
        }
    }
    const auto cellCount=[&]{auto n=need(s.cellCount)();if(n>800)throw std::invalid_argument("Frame region Cell count exceeds backing");return n;};
    const auto count=cellCount();
    if(count<=0||std::uint8_t(full))return;
    for(int i=0,n=count;i<n;){
        const auto id=need(s.cellAt)(i);auto world=need(s.center475d60)(id);world.z=0;
        const auto point=need(s.project6a27a0)(world);
        const auto x=originX,y=originY;
        const PixelPoint screen{fillSub(fillAdd(fillSub(point.x,x),viewport.x),30),fillSub(fillAdd(fillSub(point.y,y),viewport.y),15)};
        if(need(s.terrainPresent)())need(s.terrain4754b0)(need(s.cellAt)(i),screen,clip);
        n=cellCount();++i;
    }
}
}
