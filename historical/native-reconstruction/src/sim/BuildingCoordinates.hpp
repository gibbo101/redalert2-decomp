// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <functional>
#include <span>
namespace ra2 {
// Complete458930/458940 over borrowed table values. Tables and initial type
// association remain supplied; out-of-span original accesses are refused.
std::int32_t buildingFoundationWidth(std::int32_t,std::span<const std::int32_t>);
std::int32_t buildingFoundationHeight(std::int32_t,std::uint8_t extra1214,
    std::uint8_t includeExtra,std::span<const std::int32_t>);
struct BuildingCoordinateServices {
    std::function<std::int32_t(std::uint8_t)> height;
    std::function<std::int32_t()> width;
    std::function<Coord()> position88;
};
// Complete444080: height(0), width, then raw actor88. Shift/subtract/add use
// original wrapped32 arithmetic. Coordinates are returned by value; initial
// records/type/foundation association are supplied, not recovered construction.
Coord buildingCoordinates(const BuildingCoordinateServices&);
// Complete Building virtual+A8/453C70: raw88 minus128 in X/Y, wrapped32.
// Distinct from the foundation-center getter444080 above.
Coord buildingRenderCoordinates(Coord);
}
