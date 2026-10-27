// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Redraw.hpp"
#include "sim/TerrainOccupation.hpp"
#include <span>
namespace ra2 {
using StaticRedrawScan=std::function<void(std::uint8_t,const PixelRect&,const PixelRect&)>;
using StaticRedrawProjectionTrace=std::function<void(Coord)>;
// Complete static request caller in the immutable, bounded map profile. The scan
// service is the separately recovered static Terrain pass; it must not mutate
// input rectangles or collections. References retain actual argument aliasing.
void requestStaticTerrainRedraw(std::span<const TerrainCellPoint> visibleCells,
    std::span<const DirtyRegion> dirtyRegions,PixelPoint origin,const PixelRect& viewport,
    const PixelRect& firstEdge,const PixelRect& secondEdge,std::uint8_t full,
    double heightScale,const StaticRedrawScan&,const StaticRedrawProjectionTrace& trace={});
}
