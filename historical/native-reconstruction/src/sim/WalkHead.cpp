// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/WalkHead.hpp"
#include "sim/WalkHeadTransfer.hpp"
#include "sim/OriginalMath.hpp"
#include <stdexcept>

namespace ra2 {
std::uint8_t prepareWalkHead(WalkMovementState& walk,WalkHeadActor actor,
    const Coord& request,const WalkHeadInputs& inputs,const WalkHeadServices& s) {
    OriginalRounding rounding;
    const auto lookup=[&](const Coord& p) {
        if(!s.cell)throw std::invalid_argument("Walk head requires shared Cell lookup");
        return s.cell(p);
    };
    const InfantrySubcellServices subcell{s.squareRoot,
        [&](const Coord& p){return lookup(p).occupation;},s.floor,s.houseQuery};
    const auto assign=[&](Coord p) {
        walk.head.x=p.x;if(s.headStore)s.headStore(0x28,p.x);
        walk.head.y=p.y;if(s.headStore)s.headStore(0x2c,p.y);
        walk.head.z=p.z;if(s.headStore)s.headStore(0x30,p.z);
    };
    const auto nonempty=[&](const Coord& point) {
        // Each virtual query executes separately, with original short circuit
        // ordering. Do not fold this into one cached mission value.
        const auto mission=[&] {
            const auto m=unitDiscoveryMission(actor.mission);
            if(s.missionQuery)s.missionQuery(m);
            return m;
        };
        if(mission()==8||mission()==9||mission()==7||mission()==11||mission()==25) {
            if(actor.target494)throw std::invalid_argument("Walk head target-specific force selection requires recovery");
        }
        std::uint8_t elevated=0;
        const auto bridgeCell=lookup(point);
        if(bridgeCell.occupation.flags&0x100u) {
            const int savedZ=actor.position.z;
            if(!s.floor)throw std::invalid_argument("Walk head bridge decision requires floor");
            const int floor=s.floor(point);
            const int boundary=signed32(std::uint32_t(floor)+3u*std::uint32_t(inputs.levelHeight));
            elevated=std::uint8_t(savedZ>boundary);
        }
        const auto selectedCell=lookup(point);
        assign(chooseInfantrySubcell(selectedCell.occupation,point,0,elevated,
            inputs.subcells,inputs.random,inputs.bridgeHeight,subcell,s.randomDraw,inputs.empty));
        const auto effectCell=lookup(walk.head);
        if(s.cellEffect)s.cellEffect(effectCell);
        // Actual476CC0 returns AL1 before overlay effects when Cell+44==-1.
        // Its destructive/overlay children are not an admission approximation.
        if(effectCell.overlay44!=-1)throw std::invalid_argument("Walk head Cell overlay effects require recovery");
    };
    return detail::transferWalkHead(walk.head,actor.position,request,inputs.empty,
        [&](const Coord& p){releaseInfantrySubcell(p,inputs.occupationHeight,subcell,s.cellStore);},
        assign,nonempty,
        [&](const Coord& p){occupyInfantrySubcell(p,inputs.houseIndex,inputs.occupationHeight,subcell,s.cellStore);});
}
}
