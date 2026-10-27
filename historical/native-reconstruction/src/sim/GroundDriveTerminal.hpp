// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitDestination.hpp"
#include <stdexcept>

namespace ra2 {
struct AdvanceTerminalFlags {
    std::uint8_t& onMap7d;
    std::uint8_t& flag76;
    std::uint8_t& flag7a;
};
struct AdvanceTerminalServices {
    std::function<Coord(const void*)> targetCoordinates;
    std::function<std::pair<std::int16_t,std::int16_t>()> actorCell;
    std::function<Coord()> actorCoordinates;
    // These are named, supplied effects, not recovered mission implementations.
    std::function<void(int)> notify174;
    std::function<std::uint8_t(int,int)> mission414;
    std::function<std::uint8_t()> postCell490;
    std::function<void(char,int,int,std::uint32_t)> store;
    std::function<void(int)> missionQuery;
};
struct UnsupportedAdvanceTerminal : std::invalid_argument {
    explicit UnsupportedAdvanceTerminal(const char* why):std::invalid_argument(why){}
};
// The interior entry is AFTER placement, first head clear, track=-1/index=0.
// It preserves the actual AL return and the residual accumulator store, which
// the legacy void Advance entry cannot yet consume. It does not run movement.
inline bool finishOrdinaryAdvanceTerminal(UnitDestinationView v,
    AdvanceTerminalFlags flags,int heightDivisor,int residual,
    const AdvanceTerminalServices& s) {
    auto& a=v.actor;auto& d=v.drive;auto& m=d.movement;
    if(heightDivisor<=0 || m.track!=-1 || m.index!=0)
        throw UnsupportedAdvanceTerminal("Terminal entry requires cleared track/index and positive height divisor");
    const auto store=[&](char owner,int off,int width,int value){
        if(s.store)s.store(owner,off,width,std::uint32_t(value));
    };
    const auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));};
    bool arrived=false;
    if(a.target494) {
        if(!s.targetCoordinates||!s.actorCell)
            throw UnsupportedAdvanceTerminal("Terminal target/actor Cell coordinates unbound");
        const auto target=s.targetCoordinates(a.target494);
        const auto current=s.actorCell(); // Actual actor query follows target query.
        if(current.first==word(target.x) && current.second==word(target.y)) {
            if(!s.actorCoordinates)
                throw UnsupportedAdvanceTerminal("Terminal Foot coordinates unbound");
            const auto point=s.actorCoordinates();
            const int delta=signed32(std::uint32_t(point.z)-std::uint32_t(d.destination.z));
            const int distance=delta<0?signed32(0u-std::uint32_t(delta)):delta;
            const int threshold=signed32(std::uint32_t(heightDivisor)*2u);
            if(distance<threshold) {
                arrived=true;
                d.destination.x=0;store('d',0x34,4,0);
                d.destination.y=0;store('d',0x38,4,0);
                d.destination.z=0;store('d',0x3c,4,0);
                if(m.head!=Coord{}) {
                    m.head.x=0;store('d',0x40,4,0);
                    m.head.y=0;store('d',0x44,4,0);
                    m.head.z=0;store('d',0x48,4,0);
                    m.driving=false;store('d',0x63,1,0);
                }
                m.driving=false;store('d',0x63,1,0);
            }
        }
    }
    if(!s.notify174)throw UnsupportedAdvanceTerminal("Terminal notification effect unbound");
    s.notify174(2);
    if(!flags.onMap7d||flags.flag76||flags.flag7a)return true;
    if(arrived) {
        a.field490=0;store('a',0x490,4,0);
        a.target494=nullptr;store('a',0x494,4,0);
        d.route[0]=-1;store('a',0x4d0,4,-1);
        const int mission=unitDiscoveryMission(v.mission);
        if(s.missionQuery)s.missionQuery(mission);
        if(mission==2) {
            if(!s.mission414)throw UnsupportedAdvanceTerminal("Terminal mission414 effect unjoined");
            if(s.mission414(0,1))return true;
        }
    }
    if(!s.postCell490)throw UnsupportedAdvanceTerminal("Terminal postCell490 effect unjoined");
    if(s.postCell490())return true;
    if(!flags.onMap7d)return false; // Re-read after the result-bearing service.
    m.accumulator=residual;store('d',0x4c,4,residual);
    if(m.track>-1)
        throw UnsupportedAdvanceTerminal("Terminal effect resumed a movement track");
    return false;
}
}
