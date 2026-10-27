// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/GroundDriveAdvance.hpp"
namespace ra2 {
// Same movement kernel as the legacy void entry. The continuation begins after
// terminal placement/head/track/index stores and consumes the live residual.
// It must implement the original result-bearing terminal flow on this actor.
bool advanceOrdinaryGroundDriveResult(GroundDriveAdvanceState&,const DriveData&,
    int speed,double percentage,int tick,bool suppressSpeed,
    const GroundDriveAdvanceServices&,const GroundStateStore&,int queuedDirection,
    const std::function<bool(int)>& terminal);
}
