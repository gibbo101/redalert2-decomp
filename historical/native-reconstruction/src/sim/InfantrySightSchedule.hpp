// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <cstdint>
#include <functional>

namespace ra2 {
struct InfantrySightScheduleActor {
    const Coord& coordinates88;
    const std::int32_t& lastSightRange1f4;
};
struct InfantrySightScheduleServices {
    std::function<void()> missionTransition;
    std::function<void(std::uint32_t,std::uint32_t,std::uint32_t,std::uint32_t)> removeSight;
    std::function<void(std::uint32_t,std::uint32_t,std::uint32_t,std::uint32_t)> addSight;
    std::function<void(Coord,std::uint32_t,std::int32_t,std::uint32_t)> postSight;
};

// Exact interior argument-2 suffix of Infantry update-position500AA0. The
// caller/path before 501B69 and all four dispatched children remain separate.
void scheduleInfantryArrivalSight(InfantrySightScheduleActor,
    const InfantrySightScheduleServices&);
}
