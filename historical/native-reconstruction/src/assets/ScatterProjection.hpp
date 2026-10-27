// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellChildren.hpp"
#include "sim/Drive.hpp"
#include "sim/OriginalMath.hpp"
#include <bit>
namespace ra2 {
// Complete 6A6A50 coordinate-to-Cell projection. Z is not read by this root.
// It scans diagonal candidate centers and compares level-adjusted coordinates;
// it returns the unadjusted candidate. Every lookup uses the shared fallback.
inline MapInputPosition scatterProjectedCell(Coord p,const MapAttributeLookup& map){
    const auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n));};
    const auto add=[](int a,int b){return signed32(std::uint32_t(a)+std::uint32_t(b));};
    const auto sub=[](int a,int b){return signed32(std::uint32_t(a)-std::uint32_t(b));};
    const MapInputPosition origin{word(p.x/256),word(p.y/256)};
    const bool bridge=(mapAttributeCell(origin,map).flags&0x1000u)!=0;
    const int initialLevel=mapAttributeCell(origin,map).level;
    int x=add(int(origin.x)*256+128,0x600),y=add(int(origin.y)*256+128,0x600);
    // The raw candidate reaches origin within this bound for all signed-word
    // origins. The bound is native safety, not an original return/rollback.
    for(int iteration=0;iteration<512;++iteration){
        x=sub(x,8);y=sub(y,8);
        const MapInputPosition candidate{word(x/256),word(y/256)};
        const auto& cell=mapAttributeCell(candidate,map);
        int delta=int(cell.level)-initialLevel;
        if(bridge)delta=add(delta,(cell.flags&0x100u)?4:0);
        const int offset=signed32(std::uint32_t(delta)<<7);
        const auto px=word(sub(x,offset)/256),py=word(sub(y,offset)/256);
        if((px<=origin.x&&py<=origin.y)||candidate==origin)return candidate;
    }
    throw std::invalid_argument("Scatter projection exceeds native diagonal bound");
}
}
