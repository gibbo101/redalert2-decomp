// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/RadarMarkerPlacement.hpp"
#include "sim/TerrainOccupation.hpp"
namespace ra2 {
struct RadarCellNotificationFields {
    RefreshSurface* const& first1218;
    const std::int32_t &mapWidth100,&origin148C,&origin1494,&rgbWidth123C,&rgbHeight1240;
    const float& scale1484;
};
struct RadarCellNotificationServices {
    std::function<void(const RadarShapePoint&)> queue632620;
};
// Complete6328F0 with actual41FDF0 intersection and the reused FTOL semantics.
// Cell coordinates are signed words. Both surface dimensions are queried even
// when clipping produces an empty rectangle. Height/terrain are not consulted.
inline void notifyRadarCell(TerrainCellPoint cell,RadarCellNotificationFields f,
        const RadarCellNotificationServices& s){
    if(!f.first1218)return;
    auto x=fillAdd(fillSub(f.origin148C,cell.y),cell.x);
    const auto y=fillAdd(fillSub(cell.y,f.origin1494),cell.x);
    int width=2;
    if(x==-1){x=0;width=1;}
    else if(x==fillSub(fillAdd(f.mapWidth100,f.mapWidth100),1))width=1;
    const auto r=intersectFillRect({x,y,width,1},{0,0,f.rgbWidth123C,f.rgbHeight1240});
    const auto size=[&](bool height){
        auto* surface=f.first1218;
        if(!surface||!surface->table)throw std::invalid_argument("Radar notification surface owner");
        const auto& getter=height?surface->table->height80:surface->table->width7C;
        if(!getter)throw std::invalid_argument("Radar notification dimension child unbound");
        return getter(*surface);
    };
    const auto surfaceWidth=size(false),surfaceHeight=size(true);
    if(r[2]<=0||r[3]<=0)return;
    OriginalRounding rounding;
    const auto project=[&](int n){volatile double value=double(n)*double(f.scale1484);return radarProjectionInteger(value);};
    auto left=fillSub(project(r[0]),1);if(left<0)left=0;
    auto right=fillAdd(project(fillAdd(r[2],r[0])),1);if(right>=surfaceWidth)right=surfaceWidth;
    auto top=fillSub(project(r[1]),1);if(top<0)top=0;
    auto bottom=fillAdd(project(fillAdd(r[3],r[1])),1);if(bottom>=surfaceHeight)bottom=surfaceHeight;
    if(top>=bottom||left>=right)return;
    if(!s.queue632620)throw std::invalid_argument("Radar notification dirty child unbound");
    if(std::int64_t(right)-left>4096||std::int64_t(bottom)-top>4096||
       (std::int64_t(right)-left)*(std::int64_t(bottom)-top)>65536)
        throw std::invalid_argument("Radar notification execution bound");
    for(auto py=top;py<bottom;++py)for(auto px=left;px<right;++px)s.queue632620({px,py});
}
}
