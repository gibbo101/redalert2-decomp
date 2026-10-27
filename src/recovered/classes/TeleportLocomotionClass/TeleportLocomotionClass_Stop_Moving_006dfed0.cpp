// void __stdcall TeleportLocomotionClass::Stop_Moving() (0x006DFED0, ILocomotion 18)
#include "shared/teleport_locomotion.hpp"
// @ref ?unknown_coord_ac0280@@3UCoordStruct@@A=00ac0280

void __stdcall TeleportLocomotionClass::Stop_Moving()
{
    unknown_1c = unknown_coord_ac0280;
    unknown_34 = false;
    unknown_36 = false;
}
