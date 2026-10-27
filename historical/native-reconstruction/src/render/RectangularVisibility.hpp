// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TacticalViewportMatrix.hpp"
#include "render/CellVisibilityDraw.hpp"
namespace ra2 {
struct RectangularVisibilityView {
    const std::int32_t& originX;
    const std::int32_t& originY;
    const PixelRect& viewport;
    const Matrix& inverse;
};
struct RectangularVisibilityServices {
    std::function<TerrainCellPoint(Coord)> coordinateCell548000;
    std::function<bool()> terrainPresent;
    std::function<std::uint8_t(TerrainCellPoint)> permitted54aab0;
    std::function<int(TerrainCellPoint)> cell548070;
    std::function<PixelPoint(Coord)> project6a27a0;
    std::function<void(int,const PixelPoint&,const PixelRect&)> draw475520;
    std::function<void(const PixelRect&)> animation41f5e0;
};
// Complete6A7820. Borrowed map/draw services may change live origins, viewport,
// requested rectangle and registry state. Loop extents/start retain snapshots.
inline void drawRectangularVisibility(RectangularVisibilityView v,const PixelRect& requested,
        const RectangularVisibilityServices& s){
    const auto need=[](const auto& f)->const auto&{if(!f)throw std::invalid_argument("Rectangular visibility child unbound");return f;};
    OriginalRounding rounding;
    const auto x=fillSub(fillAdd(v.originX,requested.x),v.viewport.x);
    const auto y=fillSub(fillAdd(v.originY,requested.y),v.viewport.y);
    const auto output=voxelTransform(v.inverse,{float(x),float(y),0});
    const Coord world{std::max(0,tacticalFloatLow32(output.x)),std::max(0,tacticalFloatLow32(output.y)),0};
    auto start=need(s.coordinateCell548000)(world);
    start.x=std::bit_cast<std::int16_t>(std::uint16_t(std::uint16_t(start.x)-2u));
    const auto rows=fillAdd(requested.height/15,17),columns=fillAdd(requested.width/60,4);
    if(need(s.terrainPresent)()&&rows>0&&columns>0){
        if(columns>0&&std::uint64_t(rows)*std::uint32_t(columns)>1048576)
            throw std::invalid_argument("Rectangular visibility traversal exceeds execution bound");
        const auto word=[](std::int32_t n){return std::bit_cast<std::int16_t>(std::uint16_t(n));};
        for(int row=0;row<rows;++row){
            TerrainCellPoint p{word(fillAdd(start.x,row/2)),word(fillAdd(start.y,fillAdd(row,1)/2))};
            for(int col=0;col<columns;++col){
                if(need(s.permitted54aab0)(p)){
                    const auto cell=need(s.cell548070)(p);
                    // The original adds half a Cell, truncates signed /256,
                    // then rescales. Negative Cells therefore move toward zero.
                    const Coord point{((int(p.x)*256+128)/256)*256,((int(p.y)*256+128)/256)*256,0};
                    const auto projected=need(s.project6a27a0)(point);
                    const PixelPoint relative{fillSub(fillSub(projected.x,v.originX),30),fillSub(projected.y,v.originY)};
                    const PixelRect diamond{relative.x,fillAdd(relative.y,v.viewport.y),60,30};
                    const auto first=intersectFillRect({diamond.x,diamond.y,diamond.width,diamond.height},
                        {requested.x,requested.y,requested.width,requested.height});
                    const auto clip=intersectFillRect({v.viewport.x,v.viewport.y,v.viewport.width,v.viewport.height},first);
                    if(clip[2]>0&&clip[3]>0){
                        const PixelPoint screen{fillAdd(relative.x,v.viewport.x),fillAdd(relative.y,v.viewport.y)};
                        const PixelRect r{clip[0],clip[1],clip[2],clip[3]};
                        need(s.draw475520)(cell,screen,r);
                    }
                }
                p.x=word(int(p.x)+1);p.y=word(int(p.y)-1);
            }
        }
    }
    need(s.animation41f5e0)(requested); // Even absent terrain/empty traversal.
}
}
