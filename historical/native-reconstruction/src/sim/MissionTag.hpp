// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTrigger.hpp"
#include <span>

namespace ra2 {
struct MissionTagType {const std::int32_t& persistence;};
struct MissionTagTrigger {
    MissionTriggerState& state;
    const MissionTriggerServices& services;
    MissionTagTrigger* const& next;
};
struct MissionTagState {
    MissionTagType* const& type;
    MissionTagTrigger* const& first;
    std::int32_t& instances;
    std::uint8_t& executing;
};
// Last argument distinguishes a pointer store from a numeric word. Observers
// must not mutate owners. Objects/tags/triggers retain distinct native identities.
using MissionTagStore=std::function<void(const void*,std::int64_t,std::uint32_t,const void*)>;
struct MissionDeferredDelete {
    std::int32_t& capacity;
    const std::uint8_t& owns;
    std::int32_t& count;
    const std::int32_t& growth;
    std::span<const void*>& slots;
    // Heap allocation/growth is supplied; a successful callback updates live
    // backing/capacity/count as appropriate. Only its low return byte is tested.
    std::function<std::uint32_t(std::int32_t)> grow;
};
struct MissionTagOwner {MissionTagState*& tag;const void* identity;};
struct MissionTagServices {
    MissionDeferredDelete& deferred;
    const std::uint32_t& emptyCell;
    // Must borrow the actual Cell's Tag slot, including a shared fallback.
    std::function<MissionTagState*&(std::uint32_t)> cellTag;
    // Actual6ECB90 notification remains a named dependency, not Tag::Destroy.
    // RaiseEvent does not set the Tag's destroyed byte before this call.
    std::function<void(MissionTagState&,std::uint8_t)> notifyExpired;
    MissionTagStore store;
};
inline std::int32_t missionTagWrapped(std::int32_t value,std::uint32_t add) {
    return std::bit_cast<std::int32_t>(std::uint32_t(value)+add);
}
inline void appendMissionDeferredDelete(MissionDeferredDelete& q,const void* value,const MissionTagStore& store={}) {
    const auto capacity=q.capacity;
    if(q.count>=capacity) {
        if(!q.owns&&capacity)return;
        if(q.growth<=0)return;
        if(!q.grow)throw std::invalid_argument("Mission deferred deletion requires allocation service");
        const auto requested=missionTagWrapped(capacity,std::uint32_t(q.growth));
        if(!std::uint8_t(q.grow(requested)))return;
    }
    const auto index=q.count;
    if(index<0||std::size_t(index)>=q.slots.size())
        throw std::invalid_argument("Mission deferred deletion backing outside native domain");
    q.count=missionTagWrapped(index,1);if(store)store(&q,0x10,std::uint32_t(q.count),nullptr);
    q.slots[std::size_t(index)]=value;if(store)store(&q,0x100+std::int64_t(index)*4,0,value);
}
inline void destroyMissionTrigger(MissionTagTrigger& trigger,MissionDeferredDelete& q,const MissionTagStore& store={}) {
    trigger.state.destroyed=1;if(store)store(&trigger,0x2c,1,nullptr);
    appendMissionDeferredDelete(q,&trigger,store);
}
// Full Object5D4430, including same-tag remove/reinsert and wrapped counters.
inline bool setMissionObjectTag(MissionTagOwner owner,MissionTagState* incoming,const MissionTagStore& store={}) {
    if(auto* old=owner.tag) {
        old->instances=missionTagWrapped(old->instances,0xffffffffu);
        if(store)store(old,0x2c,std::uint32_t(old->instances),nullptr);
        owner.tag=nullptr;if(store)store(owner.identity,0x34,0,nullptr);
    }
    if(!incoming)return false;
    owner.tag=incoming;if(store)store(owner.identity,0x34,0,incoming);
    incoming->instances=missionTagWrapped(incoming->instances,1);
    if(store)store(incoming,0x2c,std::uint32_t(incoming->instances),nullptr);
    return true;
}
// Only the null incoming path of Cell47A460, as entered by Tag RaiseEvent.
inline void clearMissionCellTag(MissionTagState*& slot,const MissionTagStore& store={}) {
    if(auto* old=slot) {
        old->instances=missionTagWrapped(old->instances,0xffffffffu);
        if(store)store(old,0x2c,std::uint32_t(old->instances),nullptr);
    }
    slot=nullptr;if(store)store(&slot,0x3c,0,nullptr);
}
// Complete base6B3DF0 caller over recovered Trigger roots. Expiration broadcast,
// allocation and initial associations remain explicit services; no scheduler,
// original discovery producer or action effects are implied by this join.
inline bool raiseMissionTagEvent(MissionTagState& tag,MissionTriggerPulse pulse,
                                MissionTagOwner* owner,std::uint32_t location,const MissionTagServices& s) {
    if(tag.executing)return false;
    if(pulse.object!=(owner?owner->identity:nullptr))
        throw std::invalid_argument("Mission Tag owner and event object identities differ");
    bool any=false,detach=false,destroyed=false;
    auto* trigger=tag.first;
    tag.executing=1;if(s.store)s.store(&tag,0x35,1,nullptr);
    for(;trigger;trigger=trigger->next) {
        if(!tag.type)throw std::invalid_argument("Mission Tag type required");
        const auto persistence=tag.type->persistence;
        // Original SETE DL retains EDX's upper bytes before the by-value push.
        pulse.persistent=(std::uint32_t(persistence)&0xffffff00u)|std::uint32_t(persistence==2);
        if(!registerMissionTriggerEvent(trigger->state,pulse,trigger->services))continue;
        if(!tag.type)throw std::invalid_argument("Mission Tag type required");
        const auto after=tag.type->persistence;
        if(after==2) {
            (void)fireMissionTriggerActions(trigger->state,pulse.object,location,trigger->services);
            any=true;
        } else if(after==0||after==1) {
            const bool fire=after==0||tag.instances==1;
            if(fire) {
                (void)fireMissionTriggerActions(trigger->state,pulse.object,location,trigger->services);
                destroyMissionTrigger(*trigger,s.deferred,s.store);
                any=true;destroyed=true;
            }
            // Persistence1/one instance jumps past direct detachment after
            // destruction; its expiration broadcast remains a separate child.
            if(after==0||!fire)detach=true;
        }
    }
    tag.executing=0;if(s.store)s.store(&tag,0x35,0,nullptr);
    if(detach) {
        if(owner&&owner->identity&&owner->tag==&tag)(void)setMissionObjectTag(*owner,nullptr,s.store);
        if(location!=s.emptyCell) {
            if(!s.cellTag)throw std::invalid_argument("Mission Tag Cell lookup required");
            clearMissionCellTag(s.cellTag(location),s.store);
        }
    }
    if(destroyed) {
        if(!s.notifyExpired)throw std::invalid_argument("Mission Tag expiration broadcast required");
        s.notifyExpired(tag,1);
        appendMissionDeferredDelete(s.deferred,&tag,s.store);
    }
    return any;
}
}
