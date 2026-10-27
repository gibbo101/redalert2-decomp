// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/Composition.hpp"
#include <functional>

namespace ra2 {
struct BuildingFrameFields {
    const std::uint8_t& onMap7d;
    const std::uint8_t& redraw75;
    const std::uint8_t& marked74;
    std::function<Coord()> coordinatesA8;
    // Read-only diagnostic observer; not an original effect service.
    std::function<void(int,std::uint8_t)> read;
};
struct BuildingFrameRegistry {
    // Both count and backing are live. at() returns synchronous borrowed fields
    // with a lifetime covering the coordinate call. Duplicates retain identity;
    // no snapshot, ownership transfer or null-slot skip is implied.
    std::function<std::int32_t()> count;
    std::function<BuildingFrameFields(std::int32_t)> at;
};
// Shared wrapped projection used by inlined6AA180 and complete6A29D0.
// Complete6A2870 wrapped planar projection, also shared by frameWorldPosition.
PixelPoint projectTacticalPlanar(PixelPoint);
PixelPoint frameWorldPosition(Coord,double heightScale);
struct TacticalProjectionServices {
    std::function<PixelPoint()> origin;
    std::function<void(int,int)> store;
};
// Complete6A29D0, including four ordered output stores and margin result.
bool projectTacticalFrame(Coord,PixelPoint& output,double heightScale,
    const std::int32_t& width,const std::int32_t& height,const TacticalProjectionServices&);
// Complete6AA180, before frame phase dispatch. Projection is wrapped32 and
// inclusive at all four edges. The first accepted building returns immediately.
bool buildingRedrawInFrame(PixelPoint origin,PixelRect viewport,double heightScale,
                          const BuildingFrameRegistry&);
}
