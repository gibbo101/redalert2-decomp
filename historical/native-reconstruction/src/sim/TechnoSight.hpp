// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
#include <cstdint>
#include <functional>

namespace ra2 {
using TechnoSightPoint=Coord;
struct TechnoSightActor {
    const std::uint8_t& enabled32d;
    const std::uint8_t& ownerCountryFlag1a6;
    const TechnoSightPoint& coordinates88;
    const double& sightTimer118;
    std::int8_t& heightIncrease378;
    std::uint8_t& sightActive1e4;
    TechnoSightPoint& lastSightCoordinates1e8;
    std::int32_t& lastSightRange1f4;
    const void* owner=nullptr;
};
struct TechnoSightType {
    const std::uint8_t& veteranSight271;
    const std::uint8_t& eliteSight283;
    const std::int32_t& sight530;
};
struct TechnoSightRequest {
    TechnoSightPoint coordinates;
    std::int32_t range=0;
    const void* house=nullptr;
    std::uint32_t forwarded1=0,forwarded2=0;
    std::uint32_t fixed0=0,fixed1=1,fixed2=0;
};
struct TechnoSightServices {
    std::function<TechnoSightType()> type;
    std::function<const std::int32_t&()> heightDivisor1324;
    std::function<const double&()> veteranSight5a0;
    std::function<void(const TechnoSightRequest&)> revealArea;
    // Read-only trace used by exact-vector fixtures. It is not a gameplay effect.
    std::function<void(char,std::int32_t)> trace;
};

// Complete base6D5C30 sight update around the supplied reveal-area54A110 child.
// The caller owns all records. This does not recover visibility mutation,
// structure membership, scheduling, shroud drawing or any movement trigger.
void updateTechnoSight(TechnoSightActor,std::uint32_t forwarded1,
    std::uint32_t forwarded2,std::uint32_t explicitHouseOnly,
    const void* explicitHouse,const TechnoSightServices&);
}
