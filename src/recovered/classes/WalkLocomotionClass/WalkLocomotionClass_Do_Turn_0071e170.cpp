// void __stdcall WalkLocomotionClass::Do_Turn(UnknownFacingDir dir) (0x0071E170, ILocomotion 19)
// Faces the direction at once.
#include "shared/walk_locomotion.hpp"
// @ref ?Set_Current@FacingClass@@QAEXABUUnknownFacingDir@@@Z=004b8b10

void __stdcall WalkLocomotionClass::Do_Turn(UnknownFacingDir dir)
{
    LinkedTo->unknown_2e0.Set_Current(UnknownFacingDir(dir));
}
