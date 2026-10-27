// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamReadiness.hpp"
#include "sim/MissionScriptState.hpp"
namespace ra2 {
// Complete6D6E50. This field is distinct from Foot destination494.
inline void setTechnoField1B0(const void* identity,const void*& field,const void* value,const MissionTagStore& store={}){
    field=value;if(store)store(identity,0x1b0,0,value);
}
// Complete6B79E0 initial null-target path. Nonnull old/new targets enter member
// commands/map effects and must not be reduced to these two stores.
inline void clearInitialTeamTarget(TeamConstructionRecord& team,const MissionTagStore& store={}){
    if(team.value3C||team.value40)throw std::invalid_argument("Nonnull Team target replacement unjoined");
    team.value40=0;if(store)store(&team,0x40,0,nullptr);
    team.value3C=0;if(store)store(&team,0x3c,0,nullptr);
}
struct TeamScriptServices {
    std::size_t memberLimit;
    const std::uint8_t& typeAB;
    const std::uint8_t& typeEC;
    std::function<bool()> readiness6B8BB0;
    std::function<void()> anchor6B9610;
    std::function<std::uint32_t(const void*)> member1C0;
    std::function<const void*(const void*)> next4C8;
    std::function<void()> advance668920;
    std::function<bool()> hasCurrent668940;
    std::function<MissionScriptAction()> current668870;
    std::function<void(const void*)> clear6D6E50;
    std::function<void(const void*,std::uint32_t)> valueD8;
    MissionTagStore store;
    std::function<const void*(std::int32_t)> house4ED760;
    // Pure vtable association: capture the current method before House lookup.
    using Transfer=std::function<std::uint32_t(const void*,std::uint32_t)>;
    std::function<Transfer(const void*)> member378;
};
// Complete-to-return6B7AD0 active, ready, unblocked command50/20 paths. The original
// prefix and Script/target/field stores run in order. Child exceptions can follow
// original stores; callers may preflight the admitted domain before mutation.
inline void tickTeamScript(TeamConstructionRecord& team,const TeamScriptServices& s){
    if(!team.flags74[11]||team.flags74[14])throw std::invalid_argument("Team Script requires active timer-free Team");
    if(team.flags74[9]&&!requireTeamAdmission(s.readiness6B8BB0)())return;
    if(team.flags74[6])throw std::invalid_argument("Active Team restoration6B88B0 unjoined");
    requireTeamAdmission(s.anchor6B9610)();
    if(!team.flags74[5]&&s.typeAB)throw std::invalid_argument("Active Team recruitment path unjoined");
    if(!team.value54)throw std::invalid_argument("Active empty Team expiry unjoined");
    const auto blocked=std::uint8_t(requireTeamAdmission(s.member1C0)(team.value54));
    if(team.flags74[7]||team.flags74[6]||blocked)throw std::invalid_argument("Active Team regroup continuation unjoined");
    const auto put=[&](int off,std::uint8_t value){team.flags74[std::size_t(off-0x74)]=value;teamConstructionStore(s,&team,off,value);};
    const bool newCommand=team.flags74[12]!=0;
    if(newCommand){
        put(0x80,0);requireTeamAdmission(s.advance668920)();
        std::size_t visits=0;
        for(auto* cursor=team.value54;cursor;){
            if(++visits>s.memberLimit)throw std::invalid_argument("Team Script requires finite owned members");
            if(s.typeEC)throw std::invalid_argument("Team transport Script target clear unjoined");
            requireTeamAdmission(s.clear6D6E50)(cursor);
            cursor=requireTeamAdmission(s.next4C8)(cursor);
        }
        if(!requireTeamAdmission(s.hasCurrent668940)())throw std::invalid_argument("Exhausted Team Script destruction unjoined");
        clearInitialTeamTarget(team,s.store);team.value40=0;teamConstructionStore(s,&team,0x40);
    }else if(!team.value40){team.value40=team.value3C;teamConstructionStore(s,&team,0x40,0,team.value40);}
    const auto action=requireTeamAdmission(s.current668870)();
    if(action.action==20){
        std::size_t visits=0;
        for(auto* cursor=team.value54;cursor;){
            if(++visits>s.memberLimit)throw std::invalid_argument("Team Script requires finite owned transfer members");
            const auto next=requireTeamAdmission(s.next4C8)(cursor);
            const auto transfer=requireTeamAdmission(s.member378)(cursor);
            const auto house=requireTeamAdmission(s.house4ED760)(action.argument);
            (void)requireTeamAdmission(transfer)(house,1);
            cursor=next;
        }
        put(0x80,1);return;
    }
    if(action.action!=50)throw std::invalid_argument("Team Script command effect unjoined");
    if(newCommand){
        std::size_t visits=0;
        for(auto* cursor=team.value54;cursor;){
            if(++visits>s.memberLimit)throw std::invalid_argument("Team Script requires finite owned command members");
            requireTeamAdmission(s.valueD8)(cursor,std::uint32_t(action.argument));
            cursor=requireTeamAdmission(s.next4C8)(cursor);
        }
        put(0x80,1);
    }
}
// Retained entry point for existing command50 callers and original replays.
inline void tickTeamScript50(TeamConstructionRecord& team,const TeamScriptServices& s){tickTeamScript(team,s);}
}
