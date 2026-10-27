// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/RevealArea.hpp"
#include <bit>
#include <stdexcept>
namespace ra2 {
// Borrow complete548070 and the ambient10A field from the returned logical
// Cell. The host lighting record must be associated with that exact identity.
inline std::int16_t buildingCellLight(std::uint32_t packed,const RevealAreaWorld& world,
        const std::function<std::int16_t(const CellVisibilityState&)>& ambient){
    if(!ambient)throw std::invalid_argument("Building Cell ambient owner unbound");
    const TerrainCellPoint point{std::bit_cast<std::int16_t>(std::uint16_t(packed)),
        std::bit_cast<std::int16_t>(std::uint16_t(packed>>16))};
    return ambient(revealAreaMapCell(point,world));
}
}
