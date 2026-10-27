// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TechnoSight.hpp"

namespace ra2 {
struct TechnoSightRemovalActor {
    const std::uint8_t& enabled32d;
    const std::uint8_t& ownerCountryFlag1a6;
    std::uint8_t& sightActive1e4;
    const TechnoSightPoint& lastSightCoordinates1e8;
    const std::int32_t& lastSightRange1f4;
    const void* owner=nullptr;
};
struct TechnoSightRemovalServices {
    std::function<void(const TechnoSightRequest&)> revealArea;
    std::function<void(char,std::int32_t)> trace;
};

// Complete base6D5E90 old-sight removal around supplied reveal-area54A110.
void removeTechnoSight(TechnoSightRemovalActor,std::uint32_t forwarded1,
    std::uint32_t forwarded2,std::uint32_t explicitHouseOnly,
    const void* explicitHouse,const TechnoSightRemovalServices&);
}
