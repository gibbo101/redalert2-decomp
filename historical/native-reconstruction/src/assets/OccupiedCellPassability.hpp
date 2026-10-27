// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/MapOverlay.hpp"
#include <map>
namespace ra2 {
// Selected logical records, not original object layouts. Type/House/scenario
// construction and list ownership remain supplied at this boundary.
struct PassabilityOccupant {
    int kind=1,next=-1,mission=0,terrain278=0,terrain27c=0;
    std::uint8_t type1359=0,type135a=0,house142=0;
};
struct OccupiedCellPassabilityWorld {
    std::map<int,PassabilityOccupant> actors;
    int head=-1,theater=0;
    // Read-only observers. Every selected assignment is forwarded after the
    // destination is updated, including intermediate writes later overwritten.
    std::function<void(int,int)> kindQuery;
    std::function<void(int)> store;
};
// Complete passability for stable lists of actual Unit/Infantry/Building/Terrain kinds.
// Permission is obtained by the caller through the recovered map predicate.
// Alternate Cell +0xE8 members are not visited by the original root.
void updateOccupiedCellPassability(int& destination,const MapCellInput&,bool permitted,
    const MapOverlayType*,std::span<const float> wheelSpeeds,
    const OccupiedCellPassabilityWorld&);
}
