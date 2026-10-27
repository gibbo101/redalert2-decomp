// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitDiscovery.hpp"
#include <span>
namespace ra2 {
// Complete636F10: count is saved once; positive counts read links in order.
// Initial radio vector ownership/count are supplied. Invalid positive storage
// is refused only when its first missing element would be read.
bool buildingHasRadioLinks(std::int32_t count,std::span<const std::uintptr_t>);
bool buildingHasRadioPointerLinks(std::int32_t count,std::span<const void* const>);
struct BuildingDiscoveryServices {
    std::function<std::int32_t()> typeIndexB90;
    std::function<bool()> radioLinks;
    // Building4426D0 activation is still supplied, and required only if entered.
    std::function<void(std::uint8_t)> activate;
};
// Complete448FE0 around actual common6C2440 and radio636F10. Uses live owner,
// loading, House control, current/queued Mission and repeated radio queries.
bool discoverBuilding(UnitDiscoveryActor&,int discoverer,UnitDiscoveryWorld&,
    const BuildingDiscoveryServices&);
}
