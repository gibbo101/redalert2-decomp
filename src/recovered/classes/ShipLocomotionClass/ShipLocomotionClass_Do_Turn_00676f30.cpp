// void __stdcall ShipLocomotionClass::Do_Turn(UnknownFacingDir dir) (0x00676F30, ILocomotion 19)
#include "shared/ship_locomotion.hpp"
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30

void __stdcall ShipLocomotionClass::Do_Turn(UnknownFacingDir dir)
{
    LinkedTo->unknown_2e0.Set_Desired(UnknownFacingDir(dir));
}
