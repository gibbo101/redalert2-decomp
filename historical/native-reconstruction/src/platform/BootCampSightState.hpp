// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TerrainOccupation.hpp"
namespace ra2 {
// Supplied startup fields; live coordinates, enabled32D and veterancy are
// borrowed from each existing actor rather than copied into this record.
struct BootCampSightState {
    std::uint8_t ownerCountryFlag1a6=0;
    std::int8_t heightIncrease378=0;
    std::uint8_t active1e4=0;
    Coord lastCoordinates1e8{};
    std::int32_t lastRange1f4=0;
    bool operator==(const BootCampSightState&)const=default;
};
}
