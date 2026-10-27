// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/UnitVoxelStaging.hpp"
#include "render/UnitSurfaceSplit.hpp"
#include "render/FootDepth.hpp"
#include "assets/UnitDrawMetadata.hpp"
namespace ra2 {
struct UnitVoxelWorldPlanes {
    int width,height;
    std::vector<std::uint16_t>& colors;
    const std::vector<std::uint16_t>& depth;
    const std::vector<std::uint16_t>& alpha;
    const std::vector<Palette16>& palettes;
};
struct UnitVoxelWorldServices {
    UnitVoxelStagingServices actor;
    FootDepthWorld map;
    UnitDrawMetadata metadata;
    std::function<int()> baseDepth;
    std::uint32_t actor494=0;
    UnitSurfaceBridgeServices contact;
    std::function<void(const UnitSurfaceRequest&)> surface; // Optional observation.
};
// Healthy Track Unit staging -> ordinary Foot depth/gradient -> stock surface
// selection and RGB565 blits. Same map/type queries feed staging and final copy.
// Layer zero/ordinary house converter; immutable supplied map/contact/palette/
// alpha/depth planes. Base depth and shadow remain explicit services. The oracle
// executes healthy ramp-zero base depth; the caller supplies its native kernel.
// This join is not yet used by the runtime.
void drawHealthyUnitVoxelToWorld(const RasterData&,const RenderData&,
    const std::array<const VoxelModel*,3>&,const std::array<const Animation*,3>&,
    const VoxelPalette&,const UnitVoxelDrawInputs&,bool disableCache,
    UnitVoxelStagingState&,const UnitVoxelWorldServices&,const IndexRemap&,UnitVoxelWorldPlanes);
}
