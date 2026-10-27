// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/GroundUnitVoxelWorld.hpp"
#include "render/SharedUnitVoxelStaging.hpp"
namespace ra2 {
// All four original indexes belong to the selected type, with the shadow at
// +23C. Actors share this storage and the global pool, not their staging byte.
struct UnitVoxelWorldTypeIndexes {
    UnitVoxelTypeIndexes lit;
    VoxelSnapshotIndex shadow;
};
// Explicit sequential owners for the existing complete posed ground profile.
// No actor/Drive/map construction, scheduling, cache lifecycle or runtime claim.
// Observers see stores immediately, including partial state on exceptions.
void drawSharedPosedGroundUnitVoxelToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableLitCache,
    bool noShadow,bool disableShadowCache,SharedUnitVoxelStage&,
    UnitVoxelWorldTypeIndexes&,UnitVoxelActorStage&,
    const UnitVoxelWorldServices&,const GroundUnitBodyServices&,
    const GroundUnitShadowServices&,const IndexRemap&,UnitVoxelWorldPlanes,
    const UnitVoxelStore& store={});
}
