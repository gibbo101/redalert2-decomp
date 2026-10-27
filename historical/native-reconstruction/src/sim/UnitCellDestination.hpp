// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitDestination.hpp"
namespace ra2 {
// Extends the ordinary Cell/null entry to mission7. A Cell is not Techno or
// Building; its Abstract flag bit0 must be clear. Other target classes, mission16
// and active Object targets retain explicit refusals. The target flag is read at
// its original boundary, never before the same-target/mission guards.
inline void setOrdinaryUnitCellDestination(UnitDestinationView v,const void* target,
    std::uint8_t flag,const UnitDestinationProfile& p,const UnitDestinationInputs& w,
    const UnitDestinationServices& s,const std::function<std::uint8_t(const void*)>& abstractFlags){
    if(unitDiscoveryMission(v.mission)!=7&&v.mission.queuedA0!=7){
        setOrdinaryUnitDestination(v,target,flag,p,w,s);return;
    }
    using namespace unit_destination_detail;
    auto& a=v.actor;auto& d=v.drive;
    if(p.typeB1a||p.typeAf5||p.typeAe0||p.type3bc||p.passengerCount||p.passenger0||p.field5c8||!p.powered)
        throw UnsupportedUnitDestination("Cell destination excludes special type/passenger/unpowered policies");
    if(target==a.target494&&!a.forced190)return;
    a.forced190=0;store(s,'a',0x190,1,0);
    if(target)event(s,'k',0,0,11);
    const auto mission=[&](){const int m=unitDiscoveryMission(v.mission);event(s,'M',0,0,m);return m;};
    if(mission()==16||v.mission.queuedA0==16)
        throw UnsupportedUnitDestination("Cell destination mission16 policy unjoined");
    const bool mission7=mission()==7||v.mission.queuedA0==7;
    if(!mission7)throw std::logic_error("Cell destination mission changed outside supported binding");
    event(s,'x',0,0,id(s,target)); // actual Techno cast returns null for Cell/null
    if(target){
        event(s,'k',0,0,11);
        if(!abstractFlags)throw std::invalid_argument("Cell destination requires live Abstract flags");
        const auto flags=abstractFlags(target);event(s,'f',0,0,flags);
        if(flags&1)throw UnsupportedUnitDestination("Mission7 active Object target policy unjoined");
    }
    // Unlike the non7 path, this branch never writes queue word0 at 70581C.
    if(!target||flag)clearVector(a,s);
    if(target){
        if(flag)event(s,'r',0,0,0);
        const auto& h=d.movement.head;const auto& at=d.movement.actor.position;
        const bool moving=d.destination!=w.empty||(h!=w.empty&&(h.x!=at.x||h.y!=at.y));
        event(s,'v',0,0,moving);
        if(!moving){Interface retained(v,s);}
    }
    event(s,'P',0,0,p.powered);
    setOrdinaryFootDestination(v,target,p,w,s);
}
}
