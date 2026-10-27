// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/Shp.hpp"
#include "render/Composition.hpp"
#include "sim/TerrainOccupation.hpp"
#include <functional>
namespace ra2 {
// Original signed, wrapped rectangle operations, not a general geometry API.
PixelRect intersectDrawBounds(PixelRect bounds,PixelRect viewport,
                              int* adjustX=nullptr,int* adjustY=nullptr);
// Frame zero and frame count/2, including the original asymmetric extra pixel.
// Metadata is interpreted as signed SHP words. Negative frame counts are refused.
PixelRect terrainRenderBounds(const ShpImage*,PixelPoint cachedScreen,PixelPoint origin);
struct TerrainDrawGate {
    std::uint8_t bypass=0; // Unnamed original global byte; any nonzero bypasses.
    bool contextPresent=true; // Unnamed original global pointer, null also bypasses.
    std::uint8_t force=0; // Second argument's low byte.
};
struct TerrainVisibilityServices {
    std::function<PixelRect()> renderBounds;
    std::function<Coord()> coordinates;
    std::function<PixelPoint(Coord)> project;
    std::function<void(PixelPoint,PixelRect)> draw;
};
struct TerrainVisibilityEvent {char kind;int value;};
using TerrainVisibilityTrace=std::function<void(TerrainVisibilityEvent)>;
// Complete ordinary Terrain eligibility decision. Projection/draw are explicit
// services. Clears redraw and mutates caller bounds even on a later rejection.
bool drawTerrainIfVisible(TerrainMarkState&,PixelRect& bounds,PixelRect viewport,
                         TerrainDrawGate,const TerrainVisibilityServices&,
                         const TerrainVisibilityTrace& trace={});
}
