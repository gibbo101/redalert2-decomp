// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>

namespace ra2 {
struct MissionRevealObjectArgument {
    const void* identity=nullptr;
    std::uint8_t active7d=0;
};
struct MissionRevealActionServices {
    std::function<std::uint32_t(const void*,const void*,const void*,const void*,const void*)> revealAroundWaypoint;
};

// Complete base action17 branch6AE588..6AE5B4 plus its inherited dispatcher
// filter, which reduces an inactive object argument to null before the branch.
inline std::uint8_t executeMissionRevealAroundWaypointAction(
    const void* action,const void* house,MissionRevealObjectArgument object,
    const void* trigger,const void* packedCell,const MissionRevealActionServices& services) {
    if(!services.revealAroundWaypoint)throw std::invalid_argument("Mission Reveal Around Waypoint service required");
    const void* filtered=object.identity&&object.active7d?object.identity:nullptr;
    return std::uint8_t(services.revealAroundWaypoint(action,house,filtered,trigger,packedCell));
}
}
