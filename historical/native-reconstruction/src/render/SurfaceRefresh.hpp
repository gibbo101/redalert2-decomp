// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <array>
#include <cstdint>
#include <functional>
#include <stdexcept>

namespace ra2 {
using RefreshRect = std::array<std::int32_t,4>;
struct RefreshSurface;
// Logical virtual-table identity matters independently of the surface identity.
// Callers own stable tables/surfaces; no copying or SDL association is implied.
struct RefreshSurfaceVirtuals {
    std::function<void(RefreshSurface&,RefreshRect*,RefreshSurface*,RefreshRect*,std::uint32_t,std::uint32_t)> copy8;
    std::function<RefreshRect*(RefreshSurface&,RefreshRect&)> rect78;
    std::function<std::int32_t(RefreshSurface&)> width7C,height80;
};
struct RefreshSurface {
    RefreshSurfaceVirtuals* table;
    std::int32_t width,height;
};
// Complete ordinary411290/4112C0/4112D0 getter bodies. Initial geometry and
// selection of this stock virtual-table association remain supplied.
inline RefreshRect* refreshSurfaceRect(RefreshSurface& s,RefreshRect& out){
    const auto w=s.width,h=s.height;
    out[0]=0;out[1]=0;out[2]=w;out[3]=h;return &out;
}
inline std::int32_t refreshSurfaceWidth(RefreshSurface& s){return s.width;}
inline std::int32_t refreshSurfaceHeight(RefreshSurface& s){return s.height;}
struct SurfaceRefreshServices {
    const std::int32_t& modeB263D8;
    RefreshSurface* const& first1218;
    RefreshSurface* const& second121C;
    std::function<void()> finish6324A0;
    // The first two words are x/y. Other scratch words retain their incoming
    // values; this is a borrowed stack point, not a new map query or policy.
    std::function<void(RefreshRect&)> pixel632000;
};
struct SurfaceRefreshScratch { RefreshRect source,destination; };
// Complete634030 parent. Surface operations and632000/6324A0 are named leaves,
// not recovered pixel/UI effects. Scratch initialization is explicit/supplied.
inline void refreshSurfaces(const SurfaceRefreshServices& s,SurfaceRefreshScratch& scratch){
    const auto table=[](RefreshSurface* p)->RefreshSurfaceVirtuals*{
        if(!p||!p->table)throw std::invalid_argument("Missing refresh surface/table");
        return p->table;
    };
    if(s.modeB263D8==0){
        auto* savedFirst=s.first1218;
        auto* second=s.second121C;
        auto* secondTable=table(second);
        auto* savedFirstTable=table(savedFirst);
        if(!secondTable->rect78)throw std::invalid_argument("Missing refresh rect78");
        auto* source=secondTable->rect78(*second,scratch.source);
        auto* lateSecond=s.second121C;
        auto* firstTable=table(savedFirst);
        if(!firstTable->rect78)throw std::invalid_argument("Missing refresh rect78");
        auto* destination=firstTable->rect78(*savedFirst,scratch.destination);
        auto* lateFirst=s.first1218;
        if(!lateFirst||!savedFirstTable->copy8)throw std::invalid_argument("Missing refresh copy8");
        savedFirstTable->copy8(*lateFirst,destination,lateSecond,source,0,1);
        if(!s.finish6324A0)throw std::invalid_argument("Missing refresh finish6324A0");
        s.finish6324A0();return;
    }
    auto* first=s.first1218;auto* widthTable=table(first);
    if(!widthTable->width7C)throw std::invalid_argument("Missing refresh width7C");
    const auto width=widthTable->width7C(*first);
    first=s.first1218;auto* heightTable=table(first);
    if(!heightTable->height80)throw std::invalid_argument("Missing refresh height80");
    const auto height=heightTable->height80(*first);
    if(width<=0||height<=0)return;
    // Host execution bound only; not an original clamp, rollback or geometry rule.
    if(std::uint64_t(width)*std::uint64_t(height)>1048576)
        throw std::invalid_argument("Refresh pixel traversal exceeds native bound");
    for(std::int32_t y=0;y<height;++y)for(std::int32_t x=0;x<width;++x){
        scratch.source[0]=x;scratch.source[1]=y;
        if(!s.pixel632000)throw std::invalid_argument("Missing refresh pixel632000");
        s.pixel632000(scratch.source);
    }
}
}
