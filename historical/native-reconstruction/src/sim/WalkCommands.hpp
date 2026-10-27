// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/WalkMovement.hpp"
#include <stdexcept>

namespace ra2 {
struct WalkCommandActor {
    const std::int32_t& immobilized3fc;
    const std::uint8_t& disabled204;
    const std::uint8_t& disabled205;
};
struct WalkCommandServices {
    std::function<std::uint32_t(Coord)> cellFlags;
    // Scenario projection scale ABE520. Initial value remains supplied.
    std::function<const double&()> projectionScale;
    std::function<void()> resetMovement;
    // Read-only observer, using the movement kernel's L/offset/value/0 stores.
    std::function<void(char,std::int64_t,std::int64_t,std::int64_t)> trace;
};
// Actual Walk71E020; request is a by-value coordinate, not an actor target.
// This does not implement Infantry501CE0/Foot SetDestination or create a route.
void moveWalkTo(WalkMovementState&,WalkCommandActor,Coord,
    const WalkCommandServices&,Coord empty={});
// Inline so the earlier Process proof's transitive native-source guard includes
// this shared implementation as well as its caller. No original receipt changes.
inline void stopWalkMovement(WalkMovementState& w,const WalkCommandServices& s,Coord empty={}){
    const auto store=[&](int offset,std::uint32_t value){if(s.trace)s.trace('L',offset,value,0);};
    w.destination.x=empty.x;store(0x1c,std::uint32_t(w.destination.x));
    w.destination.y=empty.y;store(0x20,std::uint32_t(w.destination.y));
    w.destination.z=empty.z;store(0x24,std::uint32_t(w.destination.z));
    if(w.head==empty){
        w.moving34=0;store(0x34,0);w.reallyMoving36=0;store(0x36,0);
        if(!s.resetMovement)throw std::invalid_argument("Walk command requires movement reset");
        s.resetMovement(); // unconditional for an empty head, including stopped
    }
}
// Interface+78 is distinct from the occupation/subcell head-preparation caller.
void setWalkHeadImmediate(WalkMovementState&,Coord,const WalkCommandServices&,Coord empty={});
// Actual Infantry508750; the entered animation4DC effect remains supplied.
void resetInfantryWalkMovement(std::uint8_t& flag5cc,
    const std::function<void(int,int,int)>& animation,
    const std::function<void(char,std::int64_t,std::int64_t,std::int64_t)>& trace={});
}
