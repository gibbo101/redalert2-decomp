// void __stdcall HoverLocomotionClass::Do_Turn(UnknownFacingDir dir) (0x004FDF90, ILocomotion 19)
#include "shared/hover_locomotion.hpp"
// @ref ?Set_Desired@FacingClass@@QAE_NABUUnknownFacingDir@@@Z=004b8a30

void __stdcall HoverLocomotionClass::Do_Turn(UnknownFacingDir dir)
{
    LinkedTo->unknown_2e0.Set_Desired(UnknownFacingDir(dir));
}
