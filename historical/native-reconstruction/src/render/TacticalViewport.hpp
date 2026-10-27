// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/OriginalMath.hpp"
#include <bit>
#include <cmath>
#include <cstdint>
#include <functional>
namespace ra2 {
struct TacticalViewportState {
    std::int32_t centerX=0,centerY=0; // D64/D68; supplied camera association.
    std::int32_t originX=0,originY=0; // B0/B4.
    std::int32_t cellX=0,cellY=0,columns=0,rows=0; // D80..D8C.
};
struct TacticalViewportVector {float x=0,y=0,z=0;};
using TacticalViewportInverse=std::function<TacticalViewportVector(TacticalViewportVector)>;
using TacticalViewportStore=std::function<void(int,std::int32_t)>;
// Shared FTOL low-EAX consumer. Callers retain the inherited FP scope.
inline std::int32_t tacticalFloatLow32(float v){
    return !std::isfinite(v)||double(v)<-0x1p63||double(v)>=0x1p63?
        std::int32_t(0):std::bit_cast<std::int32_t>(std::uint32_t(std::int64_t(v)));
}
// Complete6A9170 under inherited original 0E7F FP state. Matrix591380 is an
// explicit service. Width/height are read again after that service, not cached.
inline void updateTacticalViewport(TacticalViewportState& a,const std::int32_t& width,
        const std::int32_t& height,const TacticalViewportInverse& inverse,
        const TacticalViewportStore& trace={}){
    const auto sub=[](std::int32_t x,std::int32_t y){return std::bit_cast<std::int32_t>(std::uint32_t(x)-std::uint32_t(y));};
    const auto add=[](std::int32_t x,std::uint32_t y){return std::bit_cast<std::int32_t>(std::uint32_t(x)+y);};
    const auto store=[&](int offset,std::int32_t& field,std::int32_t value){field=value;if(trace)trace(offset,value);};
    OriginalRounding rounding;
    const auto x=a.centerX,y=a.centerY;
    store(0xb0,a.originX,x);store(0xb4,a.originY,y);
    store(0xb0,a.originX,sub(x,width/2));
    const auto inputX=sub(a.originX,60);
    store(0xb4,a.originY,sub(y,height/2));
    const auto inputY=sub(a.originY,30);
    if(!inverse)throw std::invalid_argument("Tactical viewport inverse591380 unbound");
    const auto output=inverse({float(inputX),float(inputY),0});
    // FTOL returns a signed64 result; this caller uses its low32, even when
    // outside signed32. Invalid/out-of-signed64 conversion has low32 zero.
    const auto worldX=tacticalFloatLow32(output.x),worldY=tacticalFloatLow32(output.y);
    store(0xd80,a.cellX,worldX/256);store(0xd84,a.cellY,worldY/256);
    store(0xd88,a.columns,add(width/60,2));store(0xd8c,a.rows,add(height/15,4));
}
}
