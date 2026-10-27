// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
#include <stdexcept>

namespace ra2 {
struct MissionCreateTeamServices {
    // Base global A40774 is shared with other loading/admission paths. This
    // branch performs two live wrapping stores around the named child6BEC80.
    std::uint32_t& creationDepth;
    std::function<void(const void*,std::int32_t)> createTeam;
};

// Complete base action4 branch6AEC7D..6AECB2 around its named team child.
inline bool executeMissionCreateTeamAction(const void* teamType,const MissionCreateTeamServices& services) {
    services.creationDepth=services.creationDepth+1u;
    if(teamType) {
        if(!services.createTeam)throw std::invalid_argument("Mission Create Team service required");
        services.createTeam(teamType,0);
    }
    services.creationDepth=services.creationDepth-1u;
    return true;
}
}
