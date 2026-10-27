// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTagDestruction.hpp"

namespace ra2 {
// Live Tag fields consumed by Tag6B4040. This view is separate from
// MissionTagState because the callback writes Type/FirstTrigger/Destroyed.
struct MissionTagPointerReferences {
    MissionTagState& tag;
    MissionTagType*& type;
    MissionTagTrigger*& first;
    std::uint8_t& destroyed;
    const void* identity;
};
struct MissionExpiredTriggerReference {
    const void* identity;
    MissionTagTrigger* const& next;
};
// Complete6B4040 for a Trigger subject. The removed argument is intentionally
// ignored. A missing Type schedules the Tag even for an unrelated subject.
inline void expireMissionTagPointerReferences(MissionTagPointerReferences owner,
        const MissionExpiredTriggerReference& expired,std::uint32_t,
        MissionDeferredDelete& deferred,const MissionTagStore& store={}) {
    if(static_cast<const void*>(owner.type)==expired.identity) {
        owner.type=nullptr;if(store)store(owner.identity,0x24,0,nullptr);
    }
    if(static_cast<const void*>(owner.first)==expired.identity) {
        owner.first=expired.next;if(store)store(owner.identity,0x28,0,expired.next);
    }
    if(!owner.type) {
        owner.destroyed=1;if(store)store(owner.identity,0x34,1,nullptr);
        appendMissionDeferredDelete(deferred,&owner.tag,store);
    }
}
struct MissionTriggerDestructionServices {
    std::array<MissionExpirationVector<const void*>*,3> registries;
    // Complete generic expiration for kind38 remains a boundary. The production
    // join must at least dispatch the recovered Tag6B4040 recipient effect.
    std::function<void(MissionTagTrigger&,std::uint32_t)> expire;
    std::function<void(MissionTagTrigger&)> destroyBase;
    std::function<void(MissionTagTrigger&)> freeRecord;
    MissionTagStore store;
};
// Complete6EDBA0 deleting destructor after vtable projection: broadcast, one
// removal from each distinct registry, base destruction and low-bit free.
inline void destroyMissionTriggerRecord(MissionTagTrigger& trigger,std::uint32_t deleting,
                                        const MissionTriggerDestructionServices& s) {
    if(!s.expire)throw std::invalid_argument("Mission Trigger destruction expiration required");
    s.expire(trigger,1);
    for(auto* registry:s.registries) {
        if(!registry)throw std::invalid_argument("Mission Trigger destruction registry required");
        eraseMissionExpiration(*registry,
            findMissionExpiration(*registry,static_cast<const void*>(&trigger)),s.store);
    }
    if(!s.destroyBase)throw std::invalid_argument("Mission Trigger base destructor required");
    s.destroyBase(trigger);
    if(std::uint8_t(deleting)&1) {
        if(!s.freeRecord)throw std::invalid_argument("Mission Trigger free service required");
        s.freeRecord(trigger);
    }
}
inline MissionDeferredCleanupRecord bindMissionTriggerDestruction(
        MissionTagTrigger& trigger,const MissionTriggerDestructionServices& services) {
    MissionDeferredCleanupRecord record{};record.identity=&trigger;
    record.inactive=[] {return true;};record.release=[] {return std::uint32_t(1);};
    for(auto& query:record.specialType)query=[] {return false;};
    record.markSpecial=[] {throw std::invalid_argument("Trigger cannot enter Object RTTI mark path");};
    record.destroy=[&trigger,&services](std::uint32_t deleting){destroyMissionTriggerRecord(trigger,deleting,services);};
    return record;
}
}
