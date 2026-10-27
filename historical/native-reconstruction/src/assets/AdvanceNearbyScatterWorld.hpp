// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/AdvanceCellScatterWorld.hpp"
#include "sim/GroundDriveAdvanceAdmission.hpp"
#include "sim/GroundDriveAdvanceResult.hpp"
#include "sim/OriginalMath.hpp"
#include <cmath>

namespace ra2 {
// Separate complete ordinary Advance entry. The admission and movement services
// must borrow this same actor/map. Process, production ownership and runtime
// adoption are deliberately separate. Only the incoming scratch high word is
// supplied: Advance itself produces the low word before committed movement.
template<class Admission,class Motion>
inline bool advanceNearbyScatterWorld(int mover, int speed, double percentage,
    bool suppressSpeed, const GroundDriveAdvanceServices& services,
    const GroundDriveAdvanceAdmissionServices& admission, int heightDivisor,
    std::uint32_t& scratch, BasicCellUnitScatterView<Admission,Motion> world,
    const CellUnitScatterInputs& input, CellNearbySearchInputs nearby,
    const GroundStateStore& actorStore, const ScatterWorldTrace& trace,
    const NearbyLocationMapTrace& nearbyTrace,
    const std::function<bool(int)>& terminal) {
    if(mover<0 || std::size_t(mover)>=world.units.size() || !world.units[mover] ||
       world.units[mover]->mover!=mover ||
       world.veterancy.size()!=world.units.size() || !(world.veterancy[mover]<1.) ||
       world.units[mover]->profile.isTrain ||
       !admission.cell || !admission.wordCell || !admission.check || heightDivisor<=0)
        throw std::invalid_argument("Advance Scatter requires explicit actor/admission/height owners");
    auto& drive=world.units[mover]->unit.drive;
    auto& state=drive.movement;
    const int queued=drive.route[0]; // The original retains this across dispatch.
    if(!services.ground.floor || !services.ground.mark || !services.coordinateCell ||
       !services.wordCell || !services.unmarkOccupation || !services.notify ||
       !services.postCell || state.actor.bridge79 || speed<0 || speed>255 ||
       !std::isfinite(percentage) || queued < -1 || queued>7 ||
       (state.driving && state.track!=-1 && (state.track<0 || state.track>=64)))
        throw std::invalid_argument("Advance Scatter outside ordinary movement profile");
    if(state.driving && state.track!=-1) {
        OriginalRounding rounding;
        const int remaining=signed32(std::uint32_t(state.accumulator)+
            std::uint32_t(suppressSpeed?0:currentSpeed(speed,percentage)));
        if(remaining>7 && queued!=-1) {
            const auto& transition=input.driveData.transitions[std::size_t(state.track)];
            if(transition.rawTrack<1 || transition.rawTrack>6)
                throw std::invalid_argument("Advance Scatter requires ordinary track");
            scratch=(scratch&0xffff0000u)|std::uint16_t(std::uint32_t(transition.facing)<<8);
            if(trace)trace('g','I',scratch,0,0);
        }
    }
    auto bound=services;
    bound.notify=[&](int value) {
        if(!terminal && world.units[mover]->unit.actor.target494)
            throw UnsupportedUnitScatter("Advance terminal target handling remains unjoined");
        services.notify(value);
    };
    bound.rejectedSwitchAdmission=[&](Coord candidate,int direction) {
        if(trace)trace('w','V',0,0,0);
        (void)admission.cell(state.actor.position);
        const int level=admission.cell(state.actor.position).level;
        if(trace)trace('w','v',level,0,0);
        const auto word=[](int n){return std::bit_cast<std::int16_t>(std::uint16_t(n/256));};
        const auto cell=admission.wordCell(word(candidate.x),word(candidate.y));
        const int result=admission.check(cell,direction,level);
        if(result==6) {
            scatterAdvanceCellOnMap(candidate,state.actor.position,state.head,heightDivisor,
                scratch,world,input,nearby,trace,nearbyTrace);
        } else if(result!=0 && result!=2 && result!=7) {
            throw UnsupportedGroundAdmission(result);
        }
    };
    if(terminal)return advanceOrdinaryGroundDriveResult(state,input.driveData,speed,percentage,
        input.tick,suppressSpeed,bound,actorStore,queued,terminal);
    advanceOrdinaryGroundDrive(state,input.driveData,speed,percentage,input.tick,
        suppressSpeed,bound,actorStore,queued);
    return false;
}
// Legacy scope and its entered nonnull-target refusal stay explicit.
template<class Admission,class Motion>
inline void advanceWithNearbyScatter(int mover,int speed,double percentage,
    bool suppressSpeed,const GroundDriveAdvanceServices& services,
    const GroundDriveAdvanceAdmissionServices& admission,int heightDivisor,
    std::uint32_t& scratch,BasicCellUnitScatterView<Admission,Motion> world,const CellUnitScatterInputs& input,
    CellNearbySearchInputs nearby,const GroundStateStore& actorStore={},
    const ScatterWorldTrace& trace={},const NearbyLocationMapTrace& nearbyTrace={}) {
    (void)advanceNearbyScatterWorld(mover,speed,percentage,suppressSpeed,services,admission,
        heightDivisor,scratch,world,input,nearby,actorStore,trace,nearbyTrace,{});
}
}
