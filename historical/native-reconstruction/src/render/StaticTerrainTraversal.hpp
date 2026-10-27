// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TerrainVisibility.hpp"
#include <span>
namespace ra2 {
struct StaticTerrainTraversalServices {
    std::function<bool(int)> isTerrain,isDead,isAnimated,isCrumbling;
    std::function<PixelRect(int)> renderBounds;
    std::function<void(int,PixelRect&,std::uint8_t)> drawIfVisible;
    std::function<void(int)> clearRedraw;
};
// Complete ordinary static Terrain region scan. Layer order is supplied by
// recovered registration; this pass visits it in reverse. No list mutation.
void drawStaticTerrainRegion(std::span<const int> groundLayer,std::uint8_t force,
                             PixelRect dirty,PixelRect clip,PixelRect viewport,
                             const StaticTerrainTraversalServices&);
}
