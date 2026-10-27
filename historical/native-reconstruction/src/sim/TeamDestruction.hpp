// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/TeamConstruction.hpp"

namespace ra2 {
struct TeamDestructionObserver {
    const void* identity;
    const void* const& typeDC;
};
struct TeamDestructionServices {
    MissionExpirationVector<TeamDestructionObserver*>& observers;
    const std::uint8_t& activeSession;
    std::size_t memberLimit;
    // Destruction order: AC0D30, AC0D60, AC0CB0, AC0C58,866178.
    // Adapters must operate on the physical registries, including typed ones.
    std::array<std::function<void(const void*)>,5> removeFromRegistry;
    std::function<void(TeamConstructionRecord&)> projectDerivedInterfaces;
    std::function<void(const void*,bool)> notifyObserver;
    std::function<void(TeamConstructionRecord&,const void*,std::int32_t,std::uint32_t)> removeMember;
    std::function<std::int32_t(const void*)> tagInstances;
    std::function<void(const void*)> destroyTag;
    std::function<void(TeamConstructionRecord&,std::uint32_t)> expire;
    std::function<void(TeamConstructionType&,std::uint32_t)> destroyType;
    std::function<void(TeamConstructionRecord&)> destroyBase,freeRecord;
    MissionTagStore store;
};
template<class F> inline const F& requireTeamDestruction(const F& f) {
    if(!f)throw std::invalid_argument("Team destruction child unbound");
    return f;
}
// Complete6B7770. Children remain explicit: a supplied parent proof is not an
// actual-world teardown. All callback-visible associations/counts stay live.
inline void destroyTeam(TeamConstructionRecord& team,const TeamDestructionServices& s) {
    requireTeamDestruction(s.projectDerivedInterfaces)(team);
    for(std::int32_t i=0;i<s.observers.count;i=missionTagWrapped(i,1)) {
        auto* observer=missionExpirationSlot(s.observers,i);
        if(!observer)throw std::invalid_argument("Team destruction observer unbound");
        if(observer->typeDC==(team.type24?team.type24->identity:nullptr))
            requireTeamDestruction(s.notifyObserver)(observer->identity,team.flags74[15]!=0);
    }
    auto* const house=team.house2C;
    if(house&&team.type24&&team.type24->houseFlagEE) {
        --house->teamCount555C;
        teamConstructionStore(s,house->identity,0x555c,house->teamCount555C);
    }
    if(s.activeSession&&team.type24) {
        std::size_t visits=0;
        while(team.value54) {
            if(++visits>s.memberLimit)throw std::invalid_argument("Team destruction member traversal exceeds owned bound");
            requireTeamDestruction(s.removeMember)(team,team.value54,-1,0);
        }
        if(!team.type24)throw std::invalid_argument("Team destruction lost live Type after member child");
        auto& type=*team.type24;
        type.countD4=missionTagWrapped(type.countD4,0xffffffffu);
        teamConstructionStore(s,type.identity,0xd4,std::uint32_t(type.countD4));
        if(team.tag70) {
            if(!requireTeamDestruction(s.tagInstances)(team.tag70))
                requireTeamDestruction(s.destroyTag)(team.tag70);
            team.tag70=nullptr;teamConstructionStore(s,&team,0x70);
        }
    }
    requireTeamDestruction(s.expire)(team,1);
    for(const auto& remove:s.removeFromRegistry)requireTeamDestruction(remove)(&team);
    if(team.flags74[0]&&team.type24)requireTeamDestruction(s.destroyType)(*team.type24,1);
    requireTeamDestruction(s.destroyBase)(team);
}
// Complete6BE740 deleting wrapper: low bit only, and return the saved identity.
inline TeamConstructionRecord* deleteTeam(TeamConstructionRecord& team,std::uint32_t deleting,
                                          const TeamDestructionServices& s) {
    destroyTeam(team,s);
    if(deleting&1)requireTeamDestruction(s.freeRecord)(team);
    return &team;
}
}
