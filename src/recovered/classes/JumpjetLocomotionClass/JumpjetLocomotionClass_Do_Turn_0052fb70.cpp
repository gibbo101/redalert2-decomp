// void __stdcall JumpjetLocomotionClass::Do_Turn(UnknownFacingDir dir) (0x0052FB70, ILocomotion 19)
// Turns the body facing at once.
#include "shared/jumpjet_locomotion.hpp"
// @ref ?Set_Current@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8b10

void __stdcall JumpjetLocomotionClass::Do_Turn(UnknownFacingDir dir)
{
    LinkedTo->unknown_2e0.Set_Current(UnknownFacingDir(dir));
}
