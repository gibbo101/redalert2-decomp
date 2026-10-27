// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/InfantryPositionEffectsE1.hpp"
#include "sim/InfantrySightSchedule.hpp"
#include <cstdint>
#include <functional>

namespace ra2 {
struct InfantryUpdatePositionE1Actor {
    Coord& coordinates88;
    std::int32_t& queuedMissionA0;
    const void*& target494;
    const void*& alternateTarget228;
    const void*& locomotor564;
    std::int32_t& lastSightRange1f4;
    std::uint8_t& bridgeLayer79;
    std::uint8_t& onMap7d;
    std::uint8_t& special370;
    std::uint8_t& typeSpecialC14;
};
struct InfantryUpdatePositionE1Services {
    std::function<std::int32_t()> mission;
    std::function<std::uintptr_t(const Coord&)> cell;
    // Complete Object current-Cell getter. The original selected path invokes
    // it independently for each current-Cell resident query; its recovered
    // implementation performs two coordinate lookups and returns the second.
    std::function<std::uintptr_t()> currentCell;
    std::function<std::int32_t(std::uintptr_t)> cellValue;
    std::function<const void*(std::uintptr_t)> findKind6;
    std::function<const void*(std::uintptr_t,bool)> findKind2;
    std::function<const void*(std::uintptr_t,bool)> findKind1;
    std::function<std::int32_t(const void*)> targetKind;
    std::function<Coord(const void*)> targetCoordinates;
    std::function<bool(const void*)> locomotorPredicate;
    InfantrySightScheduleServices sight;
    std::function<void(std::int32_t)> postUpdate;
};

// Complete bounded argument-2 path through base Infantry update-position500AA0
// for the supplied ordinary E1 profile. Alternate mission/resident/type branches
// and the dispatched post-update child remain explicit refusals/boundaries.
void updateInfantryPositionE1(InfantryUpdatePositionE1Actor,std::int32_t argument,
    const InfantryUpdatePositionE1Services&);

// Explicit unscheduled composition of the bounded parent and its recovered
// argument-2 child. Shared actor fields must retain one logical identity.
void updateInfantryPositionE1WithEffects(InfantryUpdatePositionE1Actor,
    InfantryPositionEffectsE1Actor,std::int32_t argument,
    InfantryUpdatePositionE1Services,const InfantryPositionEffectsE1Services&);
}
