// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitVoxelStaging.hpp"
namespace ra2 {
// Explicit supplied associations for sequential ordinary Unit drawing. The
// surface/dirty rectangle/pool are shared; indexes belong to the selected type;
// the staging byte belongs to the actor. No constructor/lifetime/eviction claim.
struct SharedUnitVoxelStage {
    bool stagingSurface=false;
    UnitStaging image;
    VoxelSnapshotPool pool;
};
struct UnitVoxelTypeIndexes { std::array<VoxelSnapshotIndex,3> parts; };
struct UnitVoxelActorStage { bool staging=false; };
struct SharedUnitVoxelObservers {
    UnitVoxelStore store;
    std::function<void(const FootLitRequest&)> part;
};
void drawSharedUnitVoxelIntoStaging(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableCache,
    SharedUnitVoxelStage&,UnitVoxelTypeIndexes&,UnitVoxelActorStage&,
    const UnitVoxelStagingServices&,const IndexRemap&,
    const SharedUnitVoxelObservers& observers={});
}
