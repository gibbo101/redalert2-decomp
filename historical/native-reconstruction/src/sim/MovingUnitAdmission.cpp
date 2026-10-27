// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/MovingUnitAdmission.hpp"
#include "sim/OriginalMath.hpp"
#include <algorithm>
#include <stdexcept>
namespace ra2::admission_detail {
int directionBin(std::uint16_t heading){return (((unsigned(heading)>>12)+1)>>1)&7;}
bool isMoving(const UnitAdmissionMotionActor& a){return unit_admission_policy::isMoving(a);}
bool switchPending(const UnitAdmissionMotionActor& a,const DriveData& data){return unit_admission_policy::switchPending(a,data);}
std::optional<int> movingResident(int mover,int resident,int& result,UnitAdmissionWorld& w,const UnitAdmissionMotionWorld& motion){return unit_admission_policy::movingResident(mover,resident,result,w,motion);}
}
