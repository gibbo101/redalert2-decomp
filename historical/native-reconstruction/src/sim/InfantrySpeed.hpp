// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>
namespace ra2 {
struct InfantrySpeedActor {
    const double& veterancy118;
    const double& percentage468;
    const double& multiplier470;
    const std::uint8_t& flag5c3;
};
struct InfantrySpeedType {
    const int& speed5a0;
    const std::uint8_t& veteranSpeed26c;
    const std::uint8_t& eliteSpeed27e;
    const std::uint8_t& flagc0b;
};
struct InfantrySpeedServices {
    // Initial type/House/country/rules associations are supplied. These return
    // live fields; type and promotion queries must not be memoized.
    std::function<InfantrySpeedType()> type;
    std::function<const float&()> countrySpeed128;
    std::function<const double&()> veteranSpeed598;
    // Read-only query/conversion observer, not a gameplay callback.
    std::function<void(char,int)> trace;
};
// Complete Infantry508980 -> Foot4C9B10 speed for an Infantry body(kind15)
// and InfantryType(kind16), including actual promotion0 and integer wrapping.
// Does not recover initialization, movement commands, terrain speed or animation.
int infantrySpeed(InfantrySpeedActor,const InfantrySpeedServices&);
}
