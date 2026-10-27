// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/FootDestination.hpp"
#include "sim/WalkCommands.hpp"
#include "sim/UnitDiscovery.hpp"

namespace ra2 {
struct InfantryDestinationHouse {
    const std::int32_t& sessionA3d298;
    const std::uint8_t& human134;
    const std::uint8_t& human135;
};
struct InfantryDestinationActor {
    FootDestinationView foot;
    std::array<std::int32_t,24>& route4d0;
    const UnitDiscoveryActor& mission;
    const std::int32_t& state5ac;
    const std::uint8_t& flag5c3;
    const std::uint8_t& jumpJetB44;
    const std::uint8_t& typeC0d;
    const std::uint8_t& typeC00;
    const void* const& effect25c;
};
struct InfantryDestinationServices {
    std::function<InfantryDestinationHouse()> house;
    std::function<void(int,int,int)> animation;
    FootDestinationServices foot;
};
inline std::uint8_t infantryDestinationHuman(InfantryDestinationHouse h){
    return h.sessionA3d298?h.human134:std::uint8_t(h.human134||h.human135);
}
// Bind the existing Walk commands to the common Foot kernel; there is no
// second locomotion/target/timer implementation. The outer actor/type checks
// are separate from the locomotor's own live immobilized/disabled guards.
inline void setInfantryFootDestination(InfantryDestinationActor a,WalkMovementState& walk,
    WalkCommandActor commands,const void* target,int padding,
    const InfantryDestinationServices& s,const WalkCommandServices& ws,Coord empty={}){
    if(target&&a.effect25c)throw UnsupportedFootDestination("Infantry attached-effect destination is unjoined");
    auto services=s.foot;
    services.kind=[](){return 15;};
    services.moveTo=[&](Coord p){moveWalkTo(walk,commands,p,ws,empty);};
    services.stop=[&](){stopWalkMovement(walk,ws,empty);};
    setOrdinaryFootDestination(a.foot,target,padding,services);
}
// Complete Infantry501CE0 ordinary non-JumpJet profile. A moving/non-null
// order enters current-Cell admission and48C; it is refused until that child
// joins. Human animation4DC remains a named supplied effect. Flag is forwarded
// by the original parent; ordinary Foot does not consume it.
inline void setOrdinaryInfantryDestination(InfantryDestinationActor a,WalkMovementState& walk,
    WalkCommandActor commands,const void* target,std::uint8_t /*flag*/,int padding,
    const InfantryDestinationServices& s,const WalkCommandServices& ws,Coord empty={}){
    if(!s.house)throw std::invalid_argument("Missing Infantry destination House owner");
    const auto human=[&](){const auto value=infantryDestinationHuman(s.house());
        foot_destination_detail::event(s.foot.trace,'H',0,0,value);return value;};
    if(human()&&(a.state5ac==27||a.state5ac==28||a.state5ac==29||a.state5ac==30))return;
    if(a.jumpJetB44)throw UnsupportedFootDestination("Infantry JumpJet destination is unjoined");
    foot_destination_detail::event(s.foot.trace,'v',0,0,walk.moving34);
    if(walk.moving34&&target)throw UnsupportedFootDestination("Moving Infantry destination admission/48C is unjoined");
    if(human()&&target&&a.foot.target494==target&&a.flag5c3&&!a.typeC0d&&!a.typeC00){
        if(!s.animation)throw std::invalid_argument("Missing Infantry destination animation4DC");
        s.animation(7,0,0);
    }
    const int mission=unitDiscoveryMission(a.mission);
    foot_destination_detail::event(s.foot.trace,'M',0,0,mission);
    if(mission==7||a.mission.queuedA0==7)throw UnsupportedFootDestination("Infantry transport destination is unjoined");
    a.route4d0[0]=-1;foot_destination_detail::event(s.foot.trace,'a',0x4d0,4,0xffffffffu);
    // Recheck because entered supplied animation may alter the type record.
    if(a.jumpJetB44)throw UnsupportedFootDestination("Late Infantry JumpJet destination is unjoined");
    setInfantryFootDestination(a,walk,commands,target,padding,s,ws,empty);
}
}
