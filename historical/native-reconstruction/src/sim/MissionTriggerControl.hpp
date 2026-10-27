// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTrigger.hpp"
#include <array>
#include <span>

namespace ra2 {
struct MissionTriggerControlRecord {
    MissionTriggerState& trigger;
    const MissionTriggerServices& services;
    const std::array<std::uint8_t,3>& difficultyAllowed;
    const void* identity;
};
struct MissionTriggerControlRegistry {
    std::int32_t& count;
    std::span<MissionTriggerControlRecord*>& slots;
    // Optional typed projection from the actual live Trigger registry. It must
    // borrow that owner's slot on every query, including after removal/shifting.
    std::function<MissionTriggerControlRecord*(std::int32_t)> resolveSlot;
};
using MissionTriggerControlStore=std::function<void(const void*,std::int32_t,std::uint32_t)>;
inline MissionTriggerControlRecord& missionTriggerControlSlot(const MissionTriggerControlRegistry& registry,std::int32_t index) {
    if(registry.resolveSlot){
        if(index<0)throw std::invalid_argument("Negative Mission Trigger registry slot");
        auto* record=registry.resolveSlot(index);
        if(!record)throw std::invalid_argument("Unbound actual Mission Trigger control record");
        return *record;
    }
    if(index<0||std::size_t(index)>=registry.slots.size()||!registry.slots[std::size_t(index)])
        throw std::invalid_argument("Mission Trigger control registry outside native backing");
    return *registry.slots[std::size_t(index)];
}
// Complete base action53 helper6B1F10 and action54 branch6AF217. Target, count,
// backing, Trigger Type and difficulty inputs remain live across traversal.
inline bool setMissionTriggerTypeEnabled(MissionTriggerType* const& target,bool enable,
        const std::int32_t& difficulty,const MissionTriggerControlRegistry& registry,
        const MissionTriggerControlStore& store={}) {
    if(!target)return true;
    for(std::int32_t i=0;i<registry.count;++i) {
        auto& record=missionTriggerControlSlot(registry,i);
        if(record.trigger.type!=target)continue;
        if(enable&&difficulty>=0&&difficulty<=2&&!record.difficultyAllowed[std::size_t(difficulty)])continue;
        record.trigger.enabled=std::uint8_t(enable);
        if(store)store(record.identity,0x40,std::uint32_t(record.trigger.enabled));
        if(enable)resetMissionTriggerTimers(record.trigger,record.services);
    }
    return true;
}
}
