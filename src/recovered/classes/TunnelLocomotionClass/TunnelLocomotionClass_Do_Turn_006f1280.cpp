// void __stdcall TunnelLocomotionClass::Do_Turn(UnknownFacingDir dir) (0x006F1280, ILocomotion 19)
// Turns the linked object's body facing.
#include "shared/tunnel_locomotion.hpp"
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30

void __stdcall TunnelLocomotionClass::Do_Turn(UnknownFacingDir dir)
{
    LinkedTo->unknown_2e0.Set_Desired(UnknownFacingDir(dir));
}
