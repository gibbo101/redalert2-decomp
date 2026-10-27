// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Facing.hpp"
#include <optional>
namespace ra2 {
// Scoped constructor fields, not a complete Unit constructor or post-Unlimbo
// state. In particular, a newly constructed barrel is not the neutral pitch
// supplied by the existing voxel-draw fixture.
inline Facing initialUnitFacing(int frame,std::optional<int> rot={}) {
    Facing facing;facing.timerStart=frame;
    if(rot)facing.setRate(*rot);
    return facing;
}
struct UnitDrawingDefaults {
    Facing barrel,body,turret;
    int statusTimerStart=0,statusTimerDuration=0,layerFourValue=0,animationFrame=0;
    std::uint8_t flag204=0,flag205=0,staging=0;
};
inline UnitDrawingDefaults initialUnitDrawingFields(int frame) {
    UnitDrawingDefaults state;
    state.barrel=initialUnitFacing(frame,3);
    state.body=initialUnitFacing(frame);state.turret=initialUnitFacing(frame);
    state.statusTimerStart=frame;
    return state;
}
// Unit slot +0x32C tests a signed positive remainder, unlike the drawing
// timer's nonzero remainder decision. Preserve subtraction wrapping/order.
inline bool unitDrawingStatusActive(int start,int duration,int frame) {
    if(start==-1)return duration>0;
    const auto elapsed=signed32(std::uint32_t(frame)-std::uint32_t(start));
    if(elapsed>=duration)return false;
    return signed32(std::uint32_t(duration)-std::uint32_t(elapsed))>0;
}
}
