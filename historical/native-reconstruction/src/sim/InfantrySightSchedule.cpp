// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/InfantrySightSchedule.hpp"
#include "sim/Facing.hpp"
#include <stdexcept>

namespace ra2 {
void scheduleInfantryArrivalSight(InfantrySightScheduleActor actor,
        const InfantrySightScheduleServices& services) {
    if(!services.missionTransition||!services.removeSight||!services.addSight||!services.postSight)
        throw std::invalid_argument("Infantry sight schedule requires every ordered child");
    services.missionTransition();
    services.removeSight(0,0,0,0);
    services.addSight(0,0,0,0);
    services.postSight(actor.coordinates88,0,
        signed32(std::uint32_t(actor.lastSightRange1f4)+3u),0);
}
}
