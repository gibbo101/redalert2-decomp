// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionEvent.hpp"

namespace ra2 {
// Views borrow the live owner fields, including list links and type association.
// They neither load mission definitions nor initialize a scenario/House registry.
struct MissionTriggerEvent {
    const std::int32_t& kind;
    const std::int32_t& value;
    MissionTriggerEvent* const& next;
};
struct MissionTriggerAction { MissionTriggerAction* const& next; };
struct MissionTriggerCountry { const std::int32_t& index; };
struct MissionTriggerType {
    MissionTriggerCountry* const& country;
    MissionTriggerEvent* const& events;
    MissionTriggerAction* const& actions;
};
struct MissionTriggerState {
    MissionTriggerType* const& type;
    std::uint8_t& destroyed;
    std::uint8_t& enabled;
    MissionEventTimer& timer;
    std::int32_t& timerPadding;
    std::uint32_t& occurred;
};
struct MissionTriggerPulse {
    std::int32_t kind=0;
    const void* object=nullptr;
    std::uint32_t force=0,persistent=0;
    const void* source=nullptr;
};
struct MissionTriggerServices {
    const std::int32_t& frame;
    const std::uint8_t& suppressPulse;
    std::function<const void*(std::int32_t)> resolveHouse;
    // Original ResetTimers copies uninitialized stack scratch, not zero. Its
    // caller/ABI association is supplied until that caller is joined.
    std::function<std::int32_t()> resetPadding;
    // Actual action dispatcher/effects remain supplied. The saved packed pair
    // of Cell words is shared by all actions in one FireActions call.
    std::function<std::uint8_t(MissionTriggerAction&,const void*,const void*,
                              MissionTriggerState&,std::uint32_t&)> executeAction;
    // Read-only observations. These are not mutation/effect services.
    std::function<void(int,std::uint32_t)> store;
    std::function<void(const MissionTriggerEvent&,const void*,const MissionTriggerPulse&)> event;
};

inline void resetMissionTriggerTimers(MissionTriggerState& t,const MissionTriggerServices& s) {
    if(!t.type)throw std::invalid_argument("Mission trigger type required");
    std::uint32_t index=0;
    for(auto* event=t.type->events;event;event=event->next,++index) {
        if(event->kind==13) {
            const auto frame=s.frame;
            const auto duration=std::uint32_t(event->value)*15u;
            t.timer.start=frame;if(s.store)s.store(0x30,std::uint32_t(frame));
            if(!s.resetPadding)throw std::invalid_argument("Mission timer scratch required");
            t.timerPadding=s.resetPadding();if(s.store)s.store(0x34,std::uint32_t(t.timerPadding));
            t.timer.remaining=std::bit_cast<std::int32_t>(duration);if(s.store)s.store(0x38,duration);
            t.occurred&=~(1u<<(index&31));if(s.store)s.store(0x3c,t.occurred);
        }
        if(event->kind==51)throw std::invalid_argument("Random mission timer requires recovery");
    }
}

inline const void* missionTriggerHouse(const MissionTriggerState& t,const MissionTriggerServices& s) {
    if(!t.type||!t.type->country||!s.resolveHouse)
        throw std::invalid_argument("Mission trigger House association required");
    return s.resolveHouse(t.type->country->index);
}

// Complete base6ED740 for the recovered4/13/33/47 event paths. Event memory is
// a wrapped x86 shift mask; event32 aliases event0. No artificial32-event limit.
inline bool registerMissionTriggerEvent(MissionTriggerState& t,MissionTriggerPulse pulse,
                                       const MissionTriggerServices& s) {
    if(!t.enabled||t.destroyed)return false;
    bool all=true;
    if(!std::uint8_t(pulse.force)) {
        if(!t.type)throw std::invalid_argument("Mission trigger type required");
        std::uint32_t index=0;
        for(auto* event=t.type->events;event;event=event->next,++index) {
            const auto mask=1u<<(index&31);
            bool happened=(t.occurred&mask)!=0;
            if(!happened) {
                const auto* house=missionTriggerHouse(t,s);
                if(s.event)s.event(*event,house,pulse);
                MissionEventServices child{[&](auto country){
                    if(!s.resolveHouse)throw std::invalid_argument("Mission event House registry required");
                    (void)s.resolveHouse(country);
                }};
                happened=missionEventOccurred(event->kind,event->value,pulse.kind,s.suppressPulse,
                                              s.frame,&t.timer,child);
            }
            if(!happened){all=false;continue;}
            if(std::uint8_t(pulse.persistent)) {
                // Bounded6E6CF0 is true for4/33 and false for13/47. Its
                // second helper6E6D50 is true for all four supported kinds.
                const auto kind=event->kind;
                if(kind!=4&&kind!=33&&kind!=13&&kind!=47)
                    throw std::invalid_argument("Mission event persistence requires recovery");
                if(kind==4||kind==33){t.occurred|=mask;if(s.store)s.store(0x3c,t.occurred);}
            }
        }
    }
    if(all&&std::uint8_t(pulse.persistent))resetMissionTriggerTimers(t,s);
    return all;
}

// Complete base6ED830 traversal. Enabled/destroyed are entry checks only. False
// actions do not stop the list; the type/House and current link are read late.
inline bool fireMissionTriggerActions(MissionTriggerState& t,const void* object,
                                     std::uint32_t packedCell,const MissionTriggerServices& s) {
    if(!t.enabled||t.destroyed)return false;
    if(!t.type)throw std::invalid_argument("Mission trigger type required");
    bool any=false;
    for(auto* action=t.type->actions;action;action=action->next) {
        const auto* house=missionTriggerHouse(t,s);
        if(!s.executeAction)throw std::invalid_argument("Mission action dispatcher required");
        if(s.executeAction(*action,house,object,t,packedCell))any=true;
    }
    return any;
}
}
