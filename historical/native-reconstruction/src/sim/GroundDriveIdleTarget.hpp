// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitDestination.hpp"

namespace ra2 {
enum class GroundDriveIdleTargetResult { continueProcess, returnFalse };
struct GroundDriveIdleTargetServices {
    std::function<int(const void*)> targetKind;
    // Direct target Cell words, not its center/floor or Foot coordinates.
    // Y is read only after the X comparison succeeds.
    std::function<std::int16_t(const void*,int)> targetWord;
    // Named supplied effect. This caller ignores its AL result.
    std::function<std::uint8_t(int,int)> mission414;
    UnitDestinationServices destination;
};

// The inactive-track Process interior BEFORE Facing::IsRotating. This is a
// separate dependency, not a replacement complete Process or runtime entry.
// Actor, Drive, queue, target and command state are the actual borrowed records.
inline GroundDriveIdleTargetResult processOrdinaryIdleTarget(UnitDestinationView v,
    const UnitDestinationProfile& profile,const UnitDestinationInputs& inputs,
    const GroundDriveIdleTargetServices& s) {
    auto& a=v.actor;auto& d=v.drive;const auto& m=d.movement;
    if(m.track!=-1 && m.driving)
        throw std::invalid_argument("Idle target entry requires inactive track");
    bool arrived=false;
    if(a.target494) {
        if(!s.targetKind)throw std::invalid_argument("Idle target kind unbound");
        if(s.targetKind(a.target494)==11) {
            // The original saves this pointer after the kind query and before
            // querying actor Cell words. Never substitute target center words.
            const auto* target=a.target494;
            const auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));};
            const auto x=word(m.actor.position.x),y=word(m.actor.position.y);
            unit_destination_detail::event(s.destination,'C',x,y,0);
            if(!s.targetWord)throw std::invalid_argument("Idle target Cell words unbound");
            arrived=x==s.targetWord(target,0) && y==s.targetWord(target,1);
        }
    }
    if(!arrived)
        arrived=v.mission.mission98==5 && !m.driving && d.destination!=inputs.empty &&
            m.actor.position==d.destination;
    if(!arrived)return GroundDriveIdleTargetResult::continueProcess;
    if(a.vectorCount==0) {
        setOrdinaryUnitDestination(v,nullptr,1,profile,inputs,s.destination);
    } else {
        a.field490=0;unit_destination_detail::store(s.destination,'a',0x490,4,0);
        a.target494=nullptr;unit_destination_detail::store(s.destination,'a',0x494,4,0);
        if(!s.mission414)throw std::invalid_argument("Idle mission414 effect unbound");
        (void)s.mission414(0,1);
    }
    return GroundDriveIdleTargetResult::returnFalse;
}
}
