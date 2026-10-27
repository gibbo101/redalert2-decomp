// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamConstruction.hpp"
namespace ra2 {
struct MissionConstructionBase {
    std::int32_t index10=-1;
    std::uint8_t flags14=0,byte20=0;
    std::uint32_t value18=0,value1C=0;
};
struct MissionTriggerConstructionType {
    MissionTriggerType* identity;
    const std::array<std::uint8_t,4>& flags9C; // difficulty0/1/2, enabled9F
    MissionTriggerConstructionType* const& nextA8;
};
struct MissionTagConstructionType {
    MissionTagType* identity;
    MissionTriggerConstructionType* const& firstA0;
};
struct MissionTriggerConstructionView {
    MissionConstructionBase& base;
    MissionTagTrigger& trigger;
    MissionTriggerType*& type24;
    MissionTagTrigger*& next28;
};
struct MissionTagConstructionView {
    MissionConstructionBase& base;
    MissionTagState& tag;
    MissionTagType*& type24;
    MissionTagTrigger*& first28;
    const void*& link30;
    std::uint8_t& destroyed35;
};
struct MissionScriptConstructionRecord:MissionConstructionBase {
    const void* type24=nullptr;
    std::uint32_t value28=0;
    std::int32_t cursor2C=-1;
};
struct MissionConstructionServices {
    const std::int32_t& frame;
    const std::int32_t& difficulty;
    const void* const& tagLink30;
    // Tag:ABFE48/AC0CB0/AC0D48; Trigger:AC0CB0/AC0D48/A40AA0.
    std::array<TeamConstructionRegistry*,3> tagRegistries,triggerRegistries;
    TeamConstructionRegistry* scriptRegistry;
    std::function<const MissionTriggerConstructionType&(MissionTriggerType*)> resolveTriggerType;
    std::function<void*(std::uint32_t)> allocate;
    std::function<MissionTriggerConstructionView*(void*,MissionTriggerConstructionType&)> constructTrigger;
    // Typed projection replaces vtables. kind1=Tag,2=Trigger,3=Script;
    // phase2=base auxiliary pair,1=base four,0=derived four.
    std::function<void(const void*,unsigned,unsigned)> projectInterfaces;
    MissionTagStore store;
};
inline void constructMissionAbstract(MissionConstructionBase& r,const void* identity,
        unsigned kind,const MissionConstructionServices& s){
    struct BaseServices {
        std::function<void(MissionConstructionBase&,unsigned)> projectInterfaces;
        MissionTagStore store;
    } adapter;
    adapter.projectInterfaces=[&](auto&,unsigned phase){if(s.projectInterfaces)s.projectInterfaces(identity,kind,phase);};
    adapter.store=[&](const void*,auto off,auto value,const void* pointer){if(s.store)s.store(identity,off,value,pointer);};
    constructTeamAbstractBase(r,adapter);
}
inline void projectMissionConstruction(const void* identity,unsigned kind,const MissionConstructionServices& s){
    if(s.projectInterfaces)s.projectInterfaces(identity,kind,0);
}
inline void registerMissionConstruction(const std::array<TeamConstructionRegistry*,3>& registries,
        const void* identity,const MissionConstructionServices& s){
    for(auto* registry:registries){
        if(!registry)throw std::invalid_argument("Mission construction physical registry unbound");
        registerConstructedTeam(*registry,identity,s);
    }
}
// Complete6ED220, using the existing recovered ResetTimers on the same fields.
inline MissionTagTrigger* constructMissionTrigger(MissionTriggerConstructionView r,
        MissionTriggerConstructionType* type,const MissionConstructionServices& s){
    const auto* identity=&r.trigger;
    constructMissionAbstract(r.base,identity,2,s);
    r.type24=type?type->identity:nullptr;teamConstructionStore(s,identity,0x24,0,r.type24);
    r.next28=nullptr;teamConstructionStore(s,identity,0x28);
    auto& state=r.trigger.state;
    state.destroyed=0;teamConstructionStore(s,identity,0x2c);
    state.timer.start=s.frame;teamConstructionStore(s,identity,0x30,std::uint32_t(state.timer.start));
    state.timer.remaining=0;teamConstructionStore(s,identity,0x38);
    state.occurred=0;teamConstructionStore(s,identity,0x3c);
    state.enabled=1;teamConstructionStore(s,identity,0x40,1);
    projectMissionConstruction(identity,2,s);
    registerMissionConstruction(s.triggerRegistries,identity,s);
    if(!r.type24)return &r.trigger;
    resetMissionTriggerTimers(state,r.trigger.services);
    if(!s.resolveTriggerType)throw std::invalid_argument("Mission Trigger permission Type unbound");
    const auto& live=s.resolveTriggerType(r.type24);
    bool enabled=live.flags9C[3]!=0;
    if(enabled){
        const auto difficulty=s.difficulty;
        if(difficulty>=0&&difficulty<=2)enabled=live.flags9C[std::size_t(difficulty)]!=0;
    }
    if(!enabled){state.enabled=0;teamConstructionStore(s,identity,0x40);}
    return &r.trigger;
}
// Complete6B3870. Null Trigger allocation/child returns enter an original null
// dereference at6B39D4; refuse that unsafe domain, never silently omit a link.
inline MissionTagState* constructMissionTag(MissionTagConstructionView r,
        MissionTagConstructionType* type,const MissionConstructionServices& s){
    const auto* identity=&r.tag;
    constructMissionAbstract(r.base,identity,1,s);
    r.type24=type?type->identity:nullptr;teamConstructionStore(s,identity,0x24,0,r.type24);
    r.first28=nullptr;teamConstructionStore(s,identity,0x28);
    r.tag.instances=0;teamConstructionStore(s,identity,0x2c);
    r.link30=s.tagLink30;teamConstructionStore(s,identity,0x30,0,r.link30);
    r.tag.executing=0;teamConstructionStore(s,identity,0x34);
    r.destroyed35=0;teamConstructionStore(s,identity,0x35);
    projectMissionConstruction(identity,1,s);
    registerMissionConstruction(s.tagRegistries,identity,s);
    for(auto* cursor=type?type->firstA0:nullptr;cursor;cursor=cursor->nextA8){
        if(!s.allocate)throw std::invalid_argument("Tag Trigger allocation unbound");
        auto* storage=s.allocate(68);
        if(!storage)throw std::invalid_argument("Original Tag Trigger allocation would dereference null");
        if(!s.constructTrigger)throw std::invalid_argument("Tag Trigger constructor unbound");
        auto* child=s.constructTrigger(storage,*cursor);
        if(!child)throw std::invalid_argument("Original Tag Trigger child would dereference null");
        child->next28=r.first28;teamConstructionStore(s,&child->trigger,0x28,0,r.first28);
        r.first28=&child->trigger;teamConstructionStore(s,identity,0x28,0,r.first28);
    }
    return &r.tag;
}
// Complete668730. Script interpretation, cursor advance and destruction are
// separate producers/consumers; construction does not execute a script command.
inline MissionScriptConstructionRecord* constructMissionScript(MissionScriptConstructionRecord& r,
        const void* type,const MissionConstructionServices& s){
    constructMissionAbstract(r,&r,3,s);
    r.value28=0;teamConstructionStore(s,&r,0x28);
    r.type24=type;teamConstructionStore(s,&r,0x24,0,type);
    r.cursor2C=-1;teamConstructionStore(s,&r,0x2c,0xffffffffu);
    projectMissionConstruction(&r,3,s);
    if(!s.scriptRegistry)throw std::invalid_argument("Script physical registry unbound");
    registerConstructedTeam(*s.scriptRegistry,&r,s);
    return &r;
}
}
