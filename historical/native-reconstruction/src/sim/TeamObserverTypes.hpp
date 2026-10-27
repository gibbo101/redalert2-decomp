// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamAdmission.hpp"
#include <string_view>
#include <optional>

namespace ra2 {
struct TeamObserverTypeNames {std::string_view identifier24,name64;};
struct TeamObserverTypeLookup {
    const std::int32_t& count;
    const std::span<const void*>& slots;
    std::function<TeamObserverTypeNames(const void*)> names;
    std::function<int(std::string_view,std::string_view)> compare;
};
// Complete6BF260. Count, backing, description owner and returned slot stay live.
inline const void* findTeamObserverTeamType(std::optional<std::string_view> name,
                                           const TeamObserverTypeLookup& w){
    if(!name||w.count<=0)return nullptr;
    if(!w.names||!w.compare)throw std::invalid_argument("Observer Team Type lookup child unbound");
    const auto slot=[&](std::int32_t i){if(i<0||std::size_t(i)>=w.slots.size()||!w.slots[std::size_t(i)])throw std::invalid_argument("Observer Team Type registry unbound");return w.slots[std::size_t(i)];};
    for(std::int32_t i=0;;++i){
        if(!w.compare(*name,w.names(slot(i)).identifier24))return slot(i);
        if(!w.compare(*name,w.names(slot(i)).name64))return slot(i);
        if(i+1>=w.count)return nullptr;
    }
}
struct TeamObserverTaskForceTech {
    TeamAdmissionTaskForce task;
    const std::int32_t& sessionA3D298;
    std::function<std::int32_t(const void*)> techLevel55C;
};
// Complete6B7140. Saved count/session; a -1 level in a nonzero session resets
// the accumulator to11 even when an earlier entry produced a larger value.
inline std::int32_t teamObserverTaskForceTech(const TeamObserverTaskForceTech& w){
    const auto count=w.task.count9C;std::int32_t result=0;
    if(count<=0)return result;
    const auto session=w.sessionA3D298;
    if(std::size_t(count)>w.task.entries.size()||!w.techLevel55C)
        throw std::invalid_argument("Observer TaskForce tech owner unbound");
    for(std::int32_t i=0;i<count;++i){
        const auto p=w.task.entries[std::size_t(i)].type;
        if(!p)throw std::invalid_argument("Observer TaskForce contains null Type");
        const auto level=w.techLevel55C(p);
        if(level>result)result=level;else if(level==-1&&session)result=11;
    }
    return result;
}
}
