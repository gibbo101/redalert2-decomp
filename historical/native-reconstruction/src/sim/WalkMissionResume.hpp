// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/FootDestination.hpp"
#include "sim/InfantryMissionResume.hpp"
#include "sim/WalkMovement.hpp"
#include <bit>

namespace ra2 {
using WalkResumeTrace=FootDestinationTrace;
// Complete71FBA0 on the same Walk whose ILocomotion+4 predicate71DEA0 reads34.
inline std::uint8_t canEndWalkPiggyback(const WalkMovementState& w,const WalkResumeTrace& trace={}){
    if(trace)trace('v',0,0,w.moving34);
    if(w.moving34)return 0;
    if(trace)trace('p',0x38,0,bool(w.piggyback38));
    if(!w.piggyback38)return 0;
    if(trace)trace('p',0x35,0,w.inProcessing35);
    return std::uint8_t(!w.inProcessing35);
}
// Complete4C2DF0 positive-zero argument path. Keep the two ordered dword stores;
// a diagnostic callback may inspect or mutate the value between stores.
inline void zeroFootResumePercentage(double& percentage,const WalkResumeTrace& trace={}){
    auto bits=std::bit_cast<std::uint64_t>(percentage)&0xffffffff00000000ull;
    percentage=std::bit_cast<double>(bits);if(trace)trace('a',0x468,4,0);
    bits=std::bit_cast<std::uint64_t>(percentage)&0xffffffffull;
    percentage=std::bit_cast<double>(bits);if(trace)trace('a',0x46c,4,0);
}
// Successful Walk QueryInterface454C70 ->71FE90/71FAB0/53D2B0 for the exact
// IPiggyback IID: logical Walk+18 identity, one AddRef and late local Release.
// Null output, interface failure and deletion remain outside this retained
// ordinary profile. Original atomic calls are supplied in research; this core
// owns the single-thread reference arithmetic and original global/instance order.
inline std::uint8_t resumeWalkFootMission(FootMissionResumeActor actor,
    WalkMovementState& walk,FootDestinationReferences refs,const void* first,
    std::uint32_t second,FootMissionResumeServices services,const WalkResumeTrace& trace={}){
    services.queryPiggyback454c70=[&]()->const void*{
        if(trace)trace('B',0,0,0);
        if(!refs.instance||refs.instance>=0x7fffffffu)
            throw std::invalid_argument("Walk resume requires a retained interface");
        ++refs.global;if(trace)trace('C',0,0,refs.global);
        ++refs.instance;if(trace)trace('I',0,0,refs.instance);
        if(trace)trace('Q',0,0,1);
        return &walk;
    };
    services.predicate14=[&](const void* p)->std::uint32_t{
        if(p!=&walk)throw std::invalid_argument("Walk resume lost local interface identity");
        return canEndWalkPiggyback(walk,trace);
    };
    services.release8=[&](const void* p){
        if(p!=&walk||refs.instance<=1)throw std::invalid_argument("Walk resume release requires retained owner");
        --refs.global;if(trace)trace('C',0,0,refs.global);
        --refs.instance;if(trace)trace('I',0,0,refs.instance);
    };
    return resumeOrdinaryFootMission(actor,first,second,services);
}
}
