// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitVoxelWorld.hpp"
#include "render/ShadowVoxelWorld.hpp"
namespace ra2 {
struct UnitVoxelShadowWorldState {
    UnitVoxelStagingState unit;
    VoxelSnapshotIndex shadow;
};
// Complete healthy Unit staging/depth/final-world/shadow/cleanup join. The four
// indexes share the supplied pool. Ordinary loaded body/one-frame HVA, Track,
// ground/ramp-zero, identity global/no half scale, gradient 2/zero Z-shape only.
// Actor construction, planes/converters, heap/pool ownership/lifetime and cache
// invalidation remain supplied. The original shadow callback is observation
// only here; it runs before the actual shadow child. This is not runtime wiring.
void drawHealthyUnitVoxelAndShadowToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState&,
    const UnitVoxelWorldServices&,const IndexRemap&,UnitVoxelWorldPlanes);
}
