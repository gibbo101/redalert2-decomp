// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/PositionCloakEffect.hpp"
#include <bit>
#include <stdexcept>

namespace ra2 {
PositionCloakEffectExit applyPositionCloakEffectPrefix(PositionCloakEffectActor actor,
        const PositionCloakEffectServices& services) {
    if(!services.cell||!services.actorPredicate280)
        throw std::invalid_argument("Position cloak effect requires every service");
    const auto word=[](std::int32_t value){
        return std::bit_cast<std::int16_t>(std::uint16_t(value/256));
    };
    const TerrainCellPoint point{word(actor.coordinates88.x),word(actor.coordinates88.y)};
    const auto cell=services.cell(point);
    const auto bit=std::uint32_t(1u)<<unsigned(std::uint32_t(actor.ownerIndex)&31u);
    if(!(cell.cloakedByHouses78&bit))return PositionCloakEffectExit::CellMask;
    if(!services.actorPredicate280())return PositionCloakEffectExit::ActorPredicate;
    throw std::invalid_argument("Position cloak entered effect unsupported");
}
}
