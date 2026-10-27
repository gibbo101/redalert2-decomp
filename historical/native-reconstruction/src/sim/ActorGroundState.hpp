// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/Drive.hpp"
#include <functional>
namespace ra2 {
struct ActorGroundState {
    Coord position{};
    std::uint8_t marked74=0,bridge79=0;
};
using GroundStateStore=std::function<void(int,int)>;
struct ActorGroundServices {
    std::function<int(Coord)> floor;
    std::function<void(int)> mark;
};
// Complete Object SetHeight (relative to floor). Mark remains a supplied service;
// read position after Mark(0), write Z before Mark(1). No placement/update caller.
void setActorRelativeHeight(ActorGroundState&,int height,int bridgeHeight,
    const ActorGroundServices&,const GroundStateStore& store={});

struct DriveRampState {
    int current=0,previous=0,start=-1,padding=0,remaining=0,duration=0;
};
// Force_New_Slope initializes both ramps and a zero-duration timer. The original
// copies an uninitialized temporary padding word; make that fixture input explicit.
void initializeDriveRamp(DriveRampState&,int ramp,int tick,int temporaryPadding,
    const GroundStateStore& store={});
// Complete Drive Unlimbo wrapper: query actual current Cell then Force_New_Slope.
void unlimboDriveRamp(DriveRampState&,const std::function<std::uint8_t()>& currentRamp,
    int tick,int temporaryPadding,const GroundStateStore& store={});
// Only the Process prefix through 0x4A064A, not complete locomotion. Changed
// ramps preserve the previous ramp and restart the original three-tick timer.
void observeDriveRamp(DriveRampState&,const std::function<std::uint8_t()>& currentRamp,
    int tick,int temporaryPadding,const GroundStateStore& store={});
}
