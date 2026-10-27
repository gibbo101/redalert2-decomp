// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/TileSweep.hpp"
#include "render/SurfaceFill.hpp"
namespace ra2 {
using RadarRGB=std::array<std::uint8_t,3>;
struct RadarTerrainFields {
    const std::int32_t& globalWidthF0;
    const std::int32_t& globalOriginF8;
    const std::int32_t& minimumSum1494;
    TileSweepCursor& cursor;
    std::span<const int> slots;
    std::span<std::uint8_t>& colors1238;
};
struct RadarTerrainServices {
    // Borrow actual Cell records; do not copy coordinates into a radar world.
    std::function<const MapInputPosition&(int)> position;
    std::function<void(int,RadarRGB&,RadarRGB&)> colors4712C0;
    std::function<void(int,const TileSweepCursor&)> visit;
    FillStoreTrace store;
};
// Complete631250 with the same this/global Map owner. Iterator and intersection
// reuse recovered kernels;4712C0 remains an explicit child, not invented colors.
inline void updateRadarTerrain(const FillRect& source,const FillRect& region,
        RadarTerrainFields s,const RadarTerrainServices& services){
    if(!services.position)throw std::invalid_argument("Missing radar Cell owner");
    RadarRGB first{},second{};
    s.cursor=resetTileSweepCursor(s.globalWidthF0);
    const auto next=[&]{
        const auto id=advanceTileSweepCursor(s.cursor,s.globalWidthF0,s.slots);
        if(services.visit)services.visit(id,s.cursor);return id;
    };
    auto id=next();
    // These globals are read after the first iterator call, once per root.
    const auto offset=fillAdd(fillSub(fillAdd(s.globalOriginF8,s.globalOriginF8),s.globalWidthF0),1);
    const auto write=[&](std::uint32_t index,const RadarRGB& color){
        const auto at=index*3;
        if(std::uint64_t(at)+3>s.colors1238.size())throw std::invalid_argument("Radar RGB outside backing");
        const auto pair=std::uint32_t(color[0])|(std::uint32_t(color[1])<<8);
        s.colors1238[at]=color[0];s.colors1238[at+1]=color[1];
        if(services.store)services.store(at,2,pair);
        s.colors1238[at+2]=color[2];if(services.store)services.store(at+2,1,color[2]);
    };
    std::size_t visited=0;
    while(id!=-1){
        if(++visited>s.slots.size())throw std::invalid_argument("Unterminated radar Cell traversal");
        const auto& p=services.position(id);
        const auto x=std::int32_t(p.x),y=std::int32_t(p.y);
        if(fillAdd(x,y)>=s.minimumSum1494){
            const auto left=fillSub(fillSub(x,y),offset);
            const auto top=fillAdd(fillSub(y,s.minimumSum1494),x);
            const auto clipped=intersectFillRect(region,{left,top,2,1});
            if(clipped[2]>0&&clipped[3]>0){
                // Source stride is read before the color child, unlike RGB pointer.
                const auto index=std::uint32_t(source[2])*std::uint32_t(clipped[1])+std::uint32_t(clipped[0]);
                if(!services.colors4712C0)throw std::invalid_argument("Missing radar Cell color child");
                services.colors4712C0(id,first,second);
                if(left==fillSub(region[0],1))write(index,second);
                else if(left==fillSub(fillAdd(region[2],region[0]),1))write(index,first);
                else {write(index,first);write(index+1,second);}
            }
        }
        id=next();
    }
}
}
