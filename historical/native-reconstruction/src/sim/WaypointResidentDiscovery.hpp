// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/BuildingDiscovery.hpp"
#include <span>
#include <stdexcept>
namespace ra2 {
struct WaypointResidentDiscoveryBinding {
    int identity;
    UnitDiscoveryActor* actor;
    // Null selects common Unit discovery. Nonnull selects Building448FE0.
    const BuildingDiscoveryServices* building=nullptr;
};
// Borrow the same actor/House state used by residency and subsequent discovery.
// Initial kind/vtable association is supplied; no construction or mission schedule.
inline bool discoverWaypointResident(int identity,int house,UnitDiscoveryWorld& world,
        std::span<const WaypointResidentDiscoveryBinding> bindings){
    const WaypointResidentDiscoveryBinding* selected=nullptr;
    for(const auto& b:bindings)if(b.identity==identity){
        if(selected)throw std::invalid_argument("Ambiguous waypoint resident discovery identity");
        selected=&b;
    }
    if(!selected||!selected->actor)throw std::invalid_argument("Foreign waypoint discovery resident");
    return selected->building?discoverBuilding(*selected->actor,house,world,*selected->building):
        discoverUnit(*selected->actor,house,world);
}
}
