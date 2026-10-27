// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelPartDraw.hpp"
#include "render/UnitStaging.hpp"
namespace ra2 {
// Join the recovered part wrapper to the ordinary one-shade byte staging copy.
// The initialized converter/remap and 256x256 surface storage are caller inputs.
// Only selected flags zero are supported; the ordinary cache wrapper clears its
// caller's 0x2800 bits before invoking the part root. Other byte blitters are open.
RasterFrame drawOrdinaryVoxelPartIntoStaging(const RasterData&,const RenderData&,
    const VoxelModel&,const Animation*,const VoxelPalette&,const StagedVoxelPartInputs&,
    const StagedVoxelPartServices&,const IndexRemap&,Bytes& staging);
}
