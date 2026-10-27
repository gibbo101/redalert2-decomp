// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTagObjectExpiration.hpp"
namespace ra2 {
struct TeamExpirationRecipient {
    const void* identity;
    std::function<void(const MissionTeamExpiredAbstract&,std::uint32_t)> expired;
};
struct TeamExpirationServices {
    const void*& global680;
    const void*& global684;
    MissionExpirationVector<TeamExpirationRecipient*>& recipients; // AC0C18
    std::function<void()> clearMapSelection;
    std::function<bool(const void*)> abstractType;
    MissionTagStore store;
};
// Complete6ECB90's non-AbstractType Team34 path, actual kind child6BE730.
// Constructor-cleared Abstract bits0/1 are required; no Tag/map/logic dispatch.
inline void broadcastTeamExpiration(const MissionTeamExpiredAbstract& team,
        std::uint8_t flags14,std::uint32_t removed,const TeamExpirationServices& s) {
    if(!team.identity||(flags14&3))throw std::invalid_argument("Team expiration subject outside recovered domain");
    if(s.global680==team.identity){s.global680=nullptr;if(s.store)s.store(&s.global680,0,0,nullptr);}
    if(s.global684==team.identity){
        s.global684=nullptr;if(s.store)s.store(&s.global684,0,0,nullptr);
        if(!s.clearMapSelection)throw std::invalid_argument("Team expiration map selection child unbound");
        s.clearMapSelection();
    }
    if(!s.abstractType)throw std::invalid_argument("Team expiration RTTI association unbound");
    if(s.abstractType(team.identity))throw std::invalid_argument("Team expiration AbstractType path unjoined");
    for(std::int32_t i=0;i<s.recipients.count;i=missionTagWrapped(i,1)) {
        auto* recipient=missionExpirationSlot(s.recipients,i);
        if(!recipient||!recipient->expired)throw std::invalid_argument("Team expiration actual recipient unbound");
        recipient->expired(team,removed);
    }
}
}
