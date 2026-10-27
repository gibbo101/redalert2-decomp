// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include "sim/WalkMovement.hpp"
namespace ra2 {
inline WalkMovementCellView borrowWalkCell(const MapCellInput& c) {
    return {c.level,c.flags,&c};
}
}
