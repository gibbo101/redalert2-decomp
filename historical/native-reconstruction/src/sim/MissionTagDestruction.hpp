// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionDeferredCleanup.hpp"
#include "sim/MissionTagExpiration.hpp"

namespace ra2 {
struct MissionTagDestructionServices {
    MissionDeferredDelete& deferred;
    std::array<MissionExpirationVector<const void*>*,3> registries;
    // Complete6ECB90 is recovered separately and binds here on shared owners.
    std::function<void(MissionTagState&,std::uint32_t)> expire;
    std::function<void(MissionTagState&)> destroyBase;
    std::function<void(MissionTagState&)> freeRecord;
    MissionTagStore store;
    // Base6B39F0 has scenario bookkeeping before list cleanup. Only its ordinary
    // inactive-session branch is admitted by this bounded reconstruction.
    const std::uint8_t& sessionActive;
};
inline void destroyMissionTag(MissionTagState& tag,std::uint32_t deleting,
                              const MissionTagDestructionServices& s) {
    if(!s.expire)throw std::invalid_argument("Mission Tag destruction expiration required");
    s.expire(tag,1);
    if(s.sessionActive)
        throw std::invalid_argument("Active-session Mission Tag bookkeeping requires recovery");
    for(auto* trigger=tag.first;trigger;trigger=trigger->next)
        appendMissionDeferredDelete(s.deferred,trigger,s.store);
    for(auto* registry:s.registries) {
        if(!registry)throw std::invalid_argument("Mission Tag destruction registry required");
        eraseMissionExpiration(*registry,
            findMissionExpiration(*registry,static_cast<const void*>(&tag)),s.store);
    }
    s.expire(tag,1);
    if(!s.destroyBase)throw std::invalid_argument("Mission Tag base destructor required");
    s.destroyBase(tag);
    if(std::uint8_t(deleting)&1) {
        if(!s.freeRecord)throw std::invalid_argument("Mission Tag free service required");
        s.freeRecord(tag);
    }
}
inline MissionDeferredCleanupRecord bindMissionTagDestruction(
        MissionTagState& tag,const MissionTagDestructionServices& services) {
    MissionDeferredCleanupRecord record{};record.identity=&tag;
    record.inactive=[] {return true;};record.release=[] {return std::uint32_t(1);};
    for(auto& query:record.specialType)query=[] {return false;};
    record.markSpecial=[] {throw std::invalid_argument("Tag cannot enter Object RTTI mark path");};
    record.destroy=[&tag,&services](std::uint32_t deleting){destroyMissionTag(tag,deleting,services);};
    return record;
}
}
