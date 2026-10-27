// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitVoxelDraw.hpp"
#include "render/FootVoxelStaging.hpp"
namespace ra2 {
// Caller-owned storage; three independent type indexes share one supplied pool.
struct UnitVoxelStagingState {
    UnitVoxelDrawState draw;
    UnitStaging image;
    std::array<VoxelSnapshotIndex,3> indexes;
    VoxelSnapshotPool pool;
};
struct UnitVoxelStagingServices {
    std::function<void()> originalTypeVisible,bodyPose,multipleTurretQuery,shadowPose;
    std::function<int(int)> finalBrightness;
    std::function<void()> status,height,cell;
    std::function<std::uint8_t()> predicate;
    // Called with the composed image still present. Final world/depth and shadow
    // children remain explicit services; the shadow sees the same stencil.
    std::function<void(PixelPoint,PixelRect,int)> finalDraw;
    std::function<void(const UnitVoxelShadowRequest&)> shadow;
    StagedVoxelPartServices part;
};
// Healthy Unit -> Foot -> actual Techno raster/staging/cache protocol. Stock
// one-frame inputs; cache-entry and barrel-presence fields are derived here.
// Supplied camera/empty template/type state, successful heap
// and sufficient pool only. Clears saved dirty pixels after shadow, retaining
// the dirty rectangle. This helper is not yet used by the runtime.
void drawHealthyUnitVoxelIntoStaging(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableCache,
    UnitVoxelStagingState&,const UnitVoxelStagingServices&,const IndexRemap&);
}
