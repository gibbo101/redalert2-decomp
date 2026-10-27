// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/SurfaceFill.hpp"
namespace ra2 {
using SurfaceClipStore=std::function<void(unsigned,unsigned,std::int32_t)>;
// Complete775190 for four distinct rectangle records. Original copy/lock callers
// use distinct locals. Aliased public inputs are explicitly outside this entry.
// Trace is passive; both failed and successful calls retain all ordered stores.
inline bool clipSurfacePair(FillRect& destination,const FillRect& destinationBounds,
        FillRect& source,const FillRect& sourceBounds,const SurfaceClipStore& trace={}){
    if(&destination==&source||&destination==&destinationBounds||&destination==&sourceBounds||
       &source==&destinationBounds||&source==&sourceBounds||&destinationBounds==&sourceBounds)
        throw std::invalid_argument("Aliased surface clipping records unsupported");
    auto put=[&](unsigned owner,unsigned field,std::int32_t value){
        (owner?source:destination)[field]=value;if(trace)trace(owner,field,value);
    };
    if(destination[2]==source[2]&&destination[3]==source[3]){
        if(destination[0]<0){
            const auto x=destination[0],width=source[2];
            put(1,0,fillSub(source[0],x));put(1,2,fillAdd(x,width));
            put(0,0,0);put(0,2,fillAdd(destination[2],x));
        }
        if(destination[1]<0){
            const auto y=destination[1];
            put(1,1,fillSub(source[1],y));put(1,3,fillAdd(source[3],y));
            put(0,1,0);put(0,3,fillAdd(destination[3],y));
        }
        auto excess=fillAdd(fillSub(destination[0],destinationBounds[2]),destination[2]);
        if(excess>0){put(1,2,fillSub(source[2],excess));put(0,2,fillSub(destination[2],excess));}
        excess=fillAdd(fillSub(destination[3],destinationBounds[3]),destination[1]);
        if(excess>0){put(1,3,fillSub(source[3],excess));put(0,3,fillSub(destination[3],excess));}
        if(source[0]<0){
            const auto x=source[0];
            put(0,0,fillSub(destination[0],x));put(1,2,fillAdd(source[2],x));
            put(0,2,fillAdd(destination[2],x));put(1,0,0);
        }
        if(source[1]<0){
            const auto y=source[1];
            put(0,1,fillSub(destination[1],y));put(1,3,fillAdd(source[3],y));
            put(0,3,fillAdd(destination[3],y));put(1,1,0);
        }
        excess=fillAdd(fillSub(source[2],sourceBounds[2]),source[0]);
        if(excess>0){put(1,2,fillSub(source[2],excess));put(0,2,fillSub(destination[2],excess));}
        excess=fillAdd(fillSub(source[1],sourceBounds[3]),source[3]);
        if(excess>0){put(1,3,fillSub(source[3],excess));put(0,3,fillSub(destination[3],excess));}
    }else{
        //41FDF0 uses each requested rectangle as clip and its bounds as input.
        // Preserve this order even though ordinary intersections are symmetric.
        auto r=intersectFillRect(destination,destinationBounds);
        for(unsigned i=0;i<4;++i)put(0,i,r[i]);
        r=intersectFillRect(source,sourceBounds);
        for(unsigned i=0;i<4;++i)put(1,i,r[i]);
    }
    return destination[2]>0&&destination[3]>0&&source[2]>0&&source[3]>0;
}
}
