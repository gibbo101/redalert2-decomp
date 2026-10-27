// void __stdcall TeleportLocomotionClass::Do_Turn(UnknownFacingDir dir) (0x006E0DE0, ILocomotion 19)
#include "shared/teleport_locomotion.hpp"
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30

void __stdcall TeleportLocomotionClass::Do_Turn(UnknownFacingDir dir)
{
    LinkedTo->unknown_2e0.Set_Desired(UnknownFacingDir(dir));
}
