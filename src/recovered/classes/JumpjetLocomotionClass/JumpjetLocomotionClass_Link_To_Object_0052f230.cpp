// HRESULT __stdcall JumpjetLocomotionClass::Link_To_Object(void *object) (0x0052F230, ILocomotion 3)
// Copies the object's type's jumpjet values (the height at least twice the
// geometry constant), turns the facing at the jumpjet turn rate from 0x4000,
// then links.
#include "shared/jumpjet_locomotion.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ??0FacingClass@@QAE@H@Z=004b89f0
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10
// @ref ?Link_To_Object@LocomotionClass@@UAGJPAX@Z=0053d010

HRESULT __stdcall JumpjetLocomotionClass::Link_To_Object(void *object)
{
    TechnoClass *techno = (TechnoClass *)object;
    TurnRate = techno->unknown_slot32()->JumpjetTurnRate;
    Speed = techno->unknown_slot32()->JumpjetSpeed;
    Climb = techno->unknown_slot32()->JumpjetClimb;
    Crash = techno->unknown_slot32()->JumpjetCrash;
    int height = techno->unknown_slot32()->JumpjetHeight;
    int minimum = unknown_geometry_g * 2;
    Height = height > minimum ? height : minimum;
    Accel = techno->unknown_slot32()->JumpjetAccel;
    Wobbles = techno->unknown_slot32()->JumpjetWobbles;
    Deviation = techno->unknown_slot32()->JumpjetDeviation;
    NoWobbles = techno->unknown_slot32()->JumpjetNoWobbles;
    FacingClass facing(TurnRate);
    unknown_50 = facing;
    unknown_50.Set_Desired(UnknownFacingDir(0x4000));
    unknown_50.Set_Current(UnknownFacingDir(0x4000));
    return LocomotionClass::Link_To_Object(object);
}
