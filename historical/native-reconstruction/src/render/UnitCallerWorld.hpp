// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitDrawCaller.hpp"
#include "render/UnitVoxelShadowWorld.hpp"
namespace ra2 {
struct UnitCallerWorldServices {
    OrdinaryUnitDrawServices caller;
    UnitVoxelWorldServices world;
};
// Ordinary original-visible healthy voxel caller -> complete world/shadow draw.
// Caller map/visibility/registry/decoration services, camera, planes and actor/
// type/pool ownership remain supplied. Outer visibility is a separate wrapper.
// Optional caller.draw observes the selected arguments before the actual child.
void drawHealthyUnitCallerToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,UnitDrawResource&,const OrdinaryUnitDrawInputs&,
    PixelPoint,PixelRect,const UnitVoxelDrawInputs&,bool disableLitCache,
    bool noShadow,bool disableShadowCache,UnitVoxelShadowWorldState&,
    const UnitCallerWorldServices&,const IndexRemap&,UnitVoxelWorldPlanes,
    const UnitDrawTrace& trace={});
}
