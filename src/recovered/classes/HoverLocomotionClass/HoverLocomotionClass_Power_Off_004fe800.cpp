// bool __stdcall HoverLocomotionClass::Power_Off() (0x004FE800, ILocomotion 23)
// A powered unit on a mission starts drifting; a moving one stops.
#include "shared/hover_locomotion.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Power_Off@LocomotionClass@@UAG_NXZ=0053d210

bool __stdcall HoverLocomotionClass::Power_Off()
{
    if (Is_Powered() && LinkedTo->Mission != 0 && LinkedTo->Mission != 7) {
        unknown_68 = true;
        unknown_6c = unknown_id_source_a3d290->Random()(20, 30);
        if (unknown_id_source_a3d290->Random()(0, 99) < 50) {
            unknown_6c = -unknown_6c;
        }
    }
    if (Is_Moving()) {
        Stop_Moving();
    }
    return LocomotionClass::Power_Off();
}
