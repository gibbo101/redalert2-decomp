// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/GroundMovementPlacement.hpp"
#include "sim/GroundDriveOverlay.hpp"
namespace ra2 {
// State at the complete Advance boundary. Track selection and its head are
// supplied by the caller; IsTrain=0, no queued route, short track, acceleration, bridge,
// occupants, overlays, destination object or Passive switch in this profile.
struct GroundDriveAdvanceState {
    ActorGroundState actor;
    Coord head{};
    Facing body;
    int track=-1,index=0,accumulator=0;
    bool driving=false;
    std::uint8_t reached5a0=0,reached5a1=0;
};
struct GroundDriveAdvanceServices {
    ActorGroundServices ground;
    // The same resident/fallback identity must be returned for every query.
    // Both callbacks require ordinary nonbridge, empty, overlay-free Cells.
    std::function<const void*(Coord)> coordinateCell;
    std::function<void(std::int16_t,std::int16_t)> wordCell;
    std::function<void(Coord)> unmarkOccupation;
    // Actual Unit +0xBC returns the live +0x5A0 byte. Earlier supplied-false
    // fixtures leave this empty; the mutable membership join binds the getter.
    std::function<std::uint8_t()> occupationEligible;
    std::function<void(int)> notify;
    std::function<void()> postCell;
    // In the queued non-Passive join, the original still tests admission before
    // rejecting a mid-curve switch. No callback is needed in the queue=-1 scope.
    std::function<void(Coord,int)> rejectedSwitchAdmission;
    // Optional read-only observer at actual supported Drive stores: head words
    // +40/+44/+48, accumulator +4C, track +58, index +5C and byte +63.
    // Separate from actor stores and from preparation's admission observer.
    // An empty observer preserves earlier diagnostic streams.
    GroundStateStore driveStore;
    // Optional recovered overlay crossing. The lookup replaces the second
    // ordinary wordCell call, preserving its identity through Mark(1).
    const GroundDriveCrushingServices* crushing=nullptr;
    std::function<const void*(std::int16_t,std::int16_t)> crossingWordCell;
};
// Complete original Advance in the domain above, with actual Foot/Object/floor
// placement children. Ordinary residual interpolation does NOT SetHeight.
// This kernel is not yet called by Drive::processMovement or the SDL runtime.
void advanceOrdinaryGroundDrive(GroundDriveAdvanceState&,const DriveData&,
    int speed,double percentage,int tick,bool suppressSpeed,
    const GroundDriveAdvanceServices&,const GroundStateStore& store={},int queuedDirection=-1);
}
