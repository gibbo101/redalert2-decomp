// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/VoxelRaster.hpp"
namespace ra2 {
// Projection of the complete original initializer's shadow table. Axis/diagonal
// tilt globals remain supplied; their startup/height association is separate.
// Entries 17..20 are explicitly identity, not retained caller storage.
std::array<Matrix,21> voxelRampShadowMatrices(const RasterData&,double axisTilt,double diagonalTilt);
}
