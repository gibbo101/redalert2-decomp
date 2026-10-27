// SPDX-License-Identifier: GPL-3.0-or-later
#include "sim/UnitAdmission.hpp"
#include "sim/MovingUnitAdmission.hpp"
namespace ra2 {
int unitTerrainAdmission(int target,int direction,int& level,std::uint8_t& elevated,int previous,UnitAdmissionWorld& w){return unit_admission_policy::unitTerrainAdmission(target,direction,level,elevated,previous,w);}
int ordinaryUnitAdmission(int mover,int target,int direction,int level,int previous,std::uint8_t consult,UnitAdmissionWorld& w){return unit_admission_policy::unitAdmission(mover,target,direction,level,previous,consult,w);}
int overlayUnitAdmission(int mover,int target,int direction,int level,int previous,std::uint8_t consult,UnitAdmissionWorld& w,const UnitAdmissionOverlayServices& overlays){
    return unit_admission_policy::unitAdmission(mover,target,direction,level,previous,consult,w,
        static_cast<const UnitAdmissionMotionWorld*>(nullptr),&overlays);
}
int movingUnitAdmission(int mover,int target,int direction,int level,int previous,std::uint8_t consult,UnitAdmissionWorld& w,const UnitAdmissionMotionWorld& motion){return unit_admission_policy::unitAdmission(mover,target,direction,level,previous,consult,w,&motion);}
}
