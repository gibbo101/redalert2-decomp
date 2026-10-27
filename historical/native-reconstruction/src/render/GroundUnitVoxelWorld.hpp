// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitVoxelShadowWorld.hpp"
namespace ra2 {
struct GroundUnitBodyServices {
    // Actual Drive pose mutates the caller seed before Unit adds frame bits.
    std::function<Matrix(std::int32_t*)> pose;
    std::function<void(UnitVoxelPart,int,const Matrix&)> observePart;
};
struct GroundUnitShadowServices {
    // Actual locomotor pose/key query, followed by result-bearing relative-height
    // queries. These are independent of the lit body pose and must not be folded
    // into one cached height/Cell query.
    std::function<Matrix(std::int32_t*)> pose;
    std::function<int()> relativeHeight;
    std::function<PixelPoint()> point;
    std::function<void(const UnitVoxelShadowRequest&,PixelPoint)> observeShadow;
};
// Complete ordinary ground Track Unit -> lit staging/final world -> Drive shadow
// pose/height/point decisions -> actual raw/cached shadow pixels -> saved-dirty cleanup.
// The lit locomotor records are still supplied flat/settled. Current Cell ramps
// are supported for the shadow, with relative height <=0, no bridge/add-14/type
// alternate, one-frame body, identity global/no half scale and sufficient pool.
// Earlier flat entry points remain frozen diagnostic profiles. This profile does
// not establish floor-to-actor or locomotor ramp placement/update or runtime use.
void drawGroundUnitVoxelToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState&,
    const UnitVoxelWorldServices&,const GroundUnitShadowServices&,
    const IndexRemap&,UnitVoxelWorldPlanes);

// Extends the same drawing boundary through the ordinary positive-height shadow
// branch. Lit body state is still flat/settled; this does not join live movement
// or its stored-ramp body matrix. Keep the earlier entry point's height guard.
void drawHeightAwareGroundUnitVoxelToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState&,
    const UnitVoxelWorldServices&,const GroundUnitShadowServices&,
    const IndexRemap&,UnitVoxelWorldPlanes);
// Explicit live-body profile. The caller binds actual stored-ramp/timer/Facing
// state; shadow pose and height remain separate queries. Earlier entries retain
// their supplied flat/settled lit state and guards.
void drawPosedGroundUnitVoxelToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState&,
    const UnitVoxelWorldServices&,const GroundUnitBodyServices&,
    const GroundUnitShadowServices&,const IndexRemap&,UnitVoxelWorldPlanes);

}
