// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "render/TacticalViewport.hpp"
#include "render/VoxelRaster.hpp"

namespace ra2 {
// Complete viewport parent6A9170 with its actual point-transform591380 kernel.
// Matrix construction/association remains the caller's explicit boundary. This
// borrows the matrix; no mirrored viewport or alternate transform is created.
inline void updateTacticalViewportMatrix(TacticalViewportState& state,
        const std::int32_t& width,const std::int32_t& height,const Matrix& inverse,
        const TacticalViewportStore& trace={}) {
    updateTacticalViewport(state,width,height,[&](TacticalViewportVector input){
        const auto output=voxelTransform(inverse,{input.x,input.y,input.z});
        return TacticalViewportVector{output.x,output.y,output.z};
    },trace);
}
}
