// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/GroundDriveProcess.hpp"
#include <bit>

namespace ra2 {
// Result-bearing admission at the ordinary Advance jump point. Actor kind1,
// Passive0, ordinary tracks and all existing Advance exclusions are required.
// The separate Advance-admitted Process entry opts in; the live world/runtime
// retains its earlier guarded policy until the shared-world join is verified.
struct GroundDriveAdvanceAdmissionServices {
    std::function<GroundDriveCell(Coord)> cell;
    std::function<GroundDriveCell(std::int16_t,std::int16_t)> wordCell;
    std::function<int(const GroundDriveCell&,int,int)> check;
};
inline void advanceWithOrdinaryAdmission(GroundDriveAdvanceState& state,
    const DriveData& data,int speed,double percentage,int tick,bool suppressSpeed,
    const GroundDriveAdvanceServices& services,int queuedDirection,
    const GroundDriveAdvanceAdmissionServices& admission,
    const GroundStateStore& actorStore={}) {
    if(!admission.cell||!admission.wordCell||!admission.check)
        throw std::invalid_argument("Ordinary Advance requires result-bearing Cell/admission services");
    auto bound=services;
    bound.rejectedSwitchAdmission=[&](Coord target,int direction) {
        // Original level getter queries twice, before target word lookup. A
        // shared fallback may change its coordinates during either lookup.
        (void)admission.cell(state.actor.position);
        const int level=admission.cell(state.actor.position).level;
        const auto word=[](int n) {return std::bit_cast<std::int16_t>(std::uint16_t(n/256));};
        const auto cell=admission.wordCell(word(target.x),word(target.y));
        const int result=admission.check(cell,direction,level);
        // 0/2 enter the Unit-kind1/Passive0 rejected-switch path. 7 takes
        // the unsigned default branch directly to the index increment.
        // Other codes require distinct effects, even when the table shares
        // a continuation; this entry deliberately refuses them.
        if(result!=0&&result!=2&&result!=7)throw UnsupportedGroundAdmission(result);
    };
    advanceOrdinaryGroundDrive(state,data,speed,percentage,tick,suppressSpeed,
        bound,actorStore,queuedDirection);
}
}
