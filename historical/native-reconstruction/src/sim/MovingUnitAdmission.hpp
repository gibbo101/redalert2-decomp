// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "sim/UnitAdmission.hpp"
#include "sim/Drive.hpp"
namespace ra2 {
// Explicit supplied records for the ordinary Unit resident extension. These
// are not constructors, a command owner, or permission to move runtime Unit 1.
// Same complete ordinary admission root with actual target/Facing/Drive and
// moving allied Unit decisions. All residents are Unit-kind. Other restrictions
// of ordinaryUnitAdmission remain; special track descriptors are refused.
// The joined bearing keeps destinationDirection's +/-2^20 XY-delta bound.
int movingUnitAdmission(int mover,int target,int direction,int level,int previous,
    std::uint8_t consultLocomotor,UnitAdmissionWorld&,const UnitAdmissionMotionWorld&);
namespace admission_detail {
bool isMoving(const UnitAdmissionMotionActor&);
// Complete Drive +A4 predicate within ordinary descriptor indexes 0..6.
bool switchPending(const UnitAdmissionMotionActor&,const DriveData&);
// Null result means retain/promote the list accumulator; value 7 exits parent.
std::optional<int> movingResident(int mover,int resident,int& result,
    UnitAdmissionWorld&,const UnitAdmissionMotionWorld&);
}
}
