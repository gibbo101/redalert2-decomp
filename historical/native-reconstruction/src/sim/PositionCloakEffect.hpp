// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <cstdint>
#include <functional>

namespace ra2 {
struct PositionCloakEffectActor {
    Coord coordinates88{};
    std::int32_t ownerIndex=0;
};
struct PositionCloakEffectCell {
    std::uintptr_t identity=0;
    TerrainCellPoint point{};
    std::uint32_t cloakedByHouses78=0;
};
struct PositionCloakEffectServices {
    std::function<PositionCloakEffectCell(TerrainCellPoint)> cell;
    std::function<bool()> actorPredicate280;
};
enum class PositionCloakEffectExit : std::uint8_t {CellMask,ActorPredicate};

// Exact early-return prefix of complete base6C2990. The entered global-object
// traversal, temporary vector and actor effects remain explicitly refused.
PositionCloakEffectExit applyPositionCloakEffectPrefix(
    PositionCloakEffectActor,const PositionCloakEffectServices&);
}
