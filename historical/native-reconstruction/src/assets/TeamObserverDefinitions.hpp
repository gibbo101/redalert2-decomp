// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamObserverConstruction.hpp"
#include <string_view>
namespace ra2 {
// Borrow the persistent registry. Comparisons/children may change either field.
struct TeamObserverDefinitionRegistry {
    const std::int32_t& count;
    const std::span<TeamObserverType*>& slots;
};
struct TeamObserverDefinitionServices {
    std::function<std::int32_t(std::string_view)> entryCount;
    std::function<std::string_view(std::string_view,std::int32_t)> entryKey;
    std::function<int(std::string_view,std::string_view)> compare;
    std::function<void*(std::uint32_t)> allocate;
    std::function<TeamObserverType*(void*,std::string_view)> construct;
    std::function<bool(TeamObserverType&)> load;
    std::function<std::uint32_t(std::string_view,std::string_view,bool)> boolean;
    const std::int32_t& sessionA3D298;
    TeamObserverConstructionStore store;
};
// Complete41D540. INI enumeration, allocation and record loading are explicit
// children. Mode1 with no record would write through null in the original;
// the native bounded domain refuses at that write, retaining earlier effects.
void loadTeamObserverDefinitions(std::uint32_t mode,
    const TeamObserverDefinitionRegistry&,const TeamObserverDefinitionServices&);
}
