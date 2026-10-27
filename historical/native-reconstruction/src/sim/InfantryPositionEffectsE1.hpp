// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <cstdint>
#include <functional>

namespace ra2 {
struct InfantryPositionEffectsE1Actor {
    Coord& coordinates88;
    const void*& alternateTarget228;
    const void*& effect208;
    const void*& target34;
    std::int32_t& mode1b8;
    std::int32_t& animation418;
    std::int16_t& footprintX454;
    std::int16_t& footprintY456;
    std::uint8_t& bridge79;
    std::uint8_t& onMap7d;
    std::uint8_t& flag77;
    std::uint8_t& active32d;
    std::uint8_t& flag373;
    std::uint8_t& state59a;
    std::uint8_t& state59c;
    const std::int32_t& typeFootprint538;
};
struct InfantryPositionEffectsE1Cell {
    std::uintptr_t identity{};
    TerrainCellPoint point{};
    std::uint32_t flags140{};
    std::uint8_t flags12c{};
    const void* object3c{};
};
struct InfantryPositionEffectsE1Services {
    std::function<std::int32_t(const void*)> alternateQuery;
    std::function<std::int32_t()> mission;
    std::function<TerrainCellPoint()> cellPoint;
    std::function<InfantryPositionEffectsE1Cell(TerrainCellPoint)> cell;
    std::function<const void*(std::uintptr_t)> findKind6;
    std::function<bool(TerrainCellPoint,bool)> permission;
    std::function<void()> positionChild3b8;
    std::function<void(std::uintptr_t)> dirty;
    std::function<void(std::int32_t)> scratchStore;
    // Optional complete discovery dispatch; reads current House at the call.
    // Required only for an undiscovered actor entering revealed Cell bit0x10.
    std::function<void()> discover;
};

// Bounded ordinary E1 argument-2 path through4C7220 and its6C2B40 tail.
void applyInfantryPositionEffectsE1(InfantryPositionEffectsE1Actor,std::int32_t,
    const InfantryPositionEffectsE1Services&);
}
