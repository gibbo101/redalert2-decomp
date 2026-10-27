// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamObserverConstruction.hpp"
#include "sim/TeamObserverTypes.hpp"
#include <string>
namespace ra2 {
struct TeamObserverInputServices {
    // ReadString's decoded source value. Text/INI index construction is supplied;
    // the existing recovered bounded copy/trim reader handles its512-byte output.
    std::function<std::optional<std::string>(std::string_view)> value;
    std::function<int(std::string_view,std::string_view)> compare;
    std::function<const void*(std::string_view)> teamType;
    std::function<std::int32_t(std::string_view)> countryIndex;
    // Ordered Infantry/Unit/Aircraft/Building index queries and live backing.
    std::array<std::function<std::int32_t(std::string_view)>,4> objectIndex;
    std::array<std::function<std::span<const void*>()>,4> objectSlots;
    std::function<std::int32_t(std::string_view)> integer;
    std::function<double(std::string_view)> number;
    std::function<bool(std::int32_t)> space;
    std::function<std::uint32_t(std::string_view)> hexPair;
    // Resolve the passed live Team Type's current DC TaskForce, then query it.
    std::function<std::int32_t(const void*)> taskForceTech;
    TeamObserverConstructionStore store;
};
// Complete41D7E0 parent over actual record fields. CRT numeric/locale/tokenizer
// environment, other Type registries and INI startup remain explicit boundaries.
bool loadTeamObserverInputs(TeamObserverType&,const TeamObserverInputServices&);
}
