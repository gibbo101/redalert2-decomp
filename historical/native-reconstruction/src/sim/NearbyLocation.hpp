// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include <cstdint>
#include <functional>

namespace ra2 {
struct NearbyLocationPoint {
    std::int16_t x=0,y=0;
    bool operator==(const NearbyLocationPoint&) const = default;
};
struct NearbyLocationCell {
    std::int8_t level=0;
    std::uint32_t flags=0;
};
struct NearbyLocationOptions {
    std::int32_t speedType=0,zone=-1,movementZone=0;
    std::uint32_t alternate=0;
    std::int32_t width=1,height=1;
    std::uint8_t disallowOverlay=0,matchLevel=1,requireBurrowable=0,
        allowBridge=1,skipNorthWest=0;
};
struct NearbyLocationWorld {
    std::int32_t dimension0=0,dimension1=0,frame=0;
    NearbyLocationPoint emptyCell{};
};
struct NearbyLocationServices {
    std::function<NearbyLocationCell&(NearbyLocationPoint)> lookup;
    std::function<bool(NearbyLocationCell&,int)> permission;
    // Original rectangle checker 550CF0; NOT recovered by this parent policy.
    // The final -1 is a distinct argument, before alternate/disallowOverlay.
    std::function<bool(NearbyLocationPoint,int,int,int,int,int,int,
        std::uint32_t,std::uint8_t)> rectangle;
    std::function<bool(NearbyLocationCell&)> burrowable;
    std::function<NearbyLocationPoint(NearbyLocationPoint)> projectCenter;
    // Bind the recovered table helper, never substitute std::sqrt.
    std::function<double(double)> squareRoot;
};
// Complete 5502E0 candidate enumeration/selection policy, not route search.
// Map permission, rectangle admission, burrowability and projection are named
// services. Keep live world/closeTo references: final selection reads them late.
// Unsupported native safety domains throw after any already-consumed services;
// this function is not transactional and is not wired into the game.
NearbyLocationPoint nearbyLocation(const NearbyLocationPoint& source,
    const NearbyLocationPoint& closeTo,const NearbyLocationOptions&,
    const NearbyLocationWorld&,const NearbyLocationServices&);
}
