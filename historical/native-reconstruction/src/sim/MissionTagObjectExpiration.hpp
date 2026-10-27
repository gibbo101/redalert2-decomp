// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/MissionTagExpiration.hpp"
#include "sim/MissionExpirationPointerView.hpp"

namespace ra2 {
// Object5D3BD0's two independent references. Tag ownership uses the typed field;
// link30 is an opaque Abstract pointer chain and must not alias the Tag pointer.
struct MissionTagObjectReferences {
    MissionTagState*& tag;
    MissionExpirationPointerView link30;
    const void* identity;
};
struct MissionTagExpiredAbstract {
    MissionTagState& tag;
    const void* identity;
    const void* const& link30;
};
// A Team is an Abstract subject, never a Tag. Its successor is borrowed from
// the actual Team+30 owner; no temporary MissionTagState or Tag count exists.
struct MissionTeamExpiredAbstract {
    const void* identity;
    MissionExpirationPointerView link30;
};
inline void expireMissionTagObjectReferences(MissionTagObjectReferences object,
        const MissionTeamExpiredAbstract& expired,std::uint32_t removed,
        const MissionTagStore& store={}) {
    if(!expired.identity||static_cast<const void*>(object.tag)==expired.identity)
        throw std::invalid_argument("Team expiration cannot alias an Object Tag");
    if(std::uint8_t(removed)&&object.link30==expired.identity) {
        object.link30=static_cast<const void*>(expired.link30);
        if(store)store(object.identity,0x30,0,expired.link30);
    }
}
// Complete base Object pointer-expiration callback for a Tag subject. The full
// removed word is passed by the parent, but only its low byte controls link30.
inline void expireMissionTagObjectReferences(MissionTagObjectReferences object,
                                             const MissionTagExpiredAbstract& expired,
                                             std::uint32_t removed,
                                             const MissionTagStore& store={}) {
    if(object.tag==&expired.tag) {
        expired.tag.instances=missionTagWrapped(expired.tag.instances,0xffffffffu);
        if(store)store(&expired.tag,0x2c,std::uint32_t(expired.tag.instances),nullptr);
        object.tag=nullptr;if(store)store(object.identity,0x34,0,nullptr);
    }
    if(std::uint8_t(removed)&&object.link30==expired.identity&&expired.identity) {
        object.link30=static_cast<const void*>(expired.link30);
        if(store)store(object.identity,0x30,0,expired.link30);
    }
}
inline MissionTagExpirationRecipient bindMissionTagObjectExpiration(
        MissionTagObjectReferences object,const MissionTagExpiredAbstract& expired,
        const MissionTagStore& store={}) {
    return {object.identity,[object,&expired,store](MissionTagState& subject,std::uint32_t removed) mutable {
        if(&subject!=&expired.tag)
            throw std::invalid_argument("Mission expiration subject association differs");
        expireMissionTagObjectReferences(object,expired,removed,store);
    }};
}
// Shared-owner composition: the already recovered RaiseEvent calls the recovered
// Tag44 broadcast directly. It does not drain the deferred queue or own records.
inline bool raiseMissionTagEventWithExpiration(MissionTagState& tag,MissionTriggerPulse pulse,
        MissionTagOwner* owner,std::uint32_t location,const MissionTagServices& base,
        const MissionTagExpirationServices& expiration) {
    MissionTagServices joined{base.deferred,base.emptyCell,base.cellTag,{},base.store};
    joined.notifyExpired=[&](MissionTagState& expired,std::uint8_t removed) {
        broadcastMissionTagExpiration(expired,removed,expiration);
    };
    return raiseMissionTagEvent(tag,pulse,owner,location,joined);
}
}
