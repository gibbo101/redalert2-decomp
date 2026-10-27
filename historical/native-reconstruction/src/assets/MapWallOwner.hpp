// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapCellInputs.hpp"
#include "sim/Drive.hpp"
#include <functional>
#include <span>

namespace ra2 {
struct WallOwnerBuilding {
    std::uint8_t active=0,onMap=0,wallOwner=0;
};
struct WallOwnerServices {
    // Read-only services over a stable registry. Distance may nest the recovered
    // Cell-target helper below; owner is the actual candidate's house array index.
    std::function<int(std::size_t)> distance,owner;
    std::function<void(int)> store;
};
// Complete Cell owner selection. No overlay/nonwall leaves preserve the owner.
// Type/house/registry construction and dynamic ownership remain outside this API.
void assignMapWallOwner(int overlay,std::uint8_t wall,int& owner,
    std::span<const WallOwnerBuilding>,const WallOwnerServices&);

// Actual ordinary coordinate getters. Cell height is the explicit terrain-height
// service; foundation dimensions are supplied results of the original type table.
Coord wallOwnerCellCoordinates(MapInputPosition,int height);
Coord wallOwnerBuildingCoordinates(Coord,int width,int height);
// Distance helper restricted to a Cell target (kind 11), with the supplied
// 53-bit/toward-zero caller FP mode used by the exact-engine test profile. The original
// building-target foundation subtraction is excluded, not applied to Cell targets.
// Pass the recovered table sqrt; std::sqrt is not an equivalent substitution.
int wallOwnerCellDistance(Coord building,Coord cell,
    const std::function<double(double)>& tableSquareRoot);
}
