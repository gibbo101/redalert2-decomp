// bool __stdcall FlyLocomotionClass::Power_Off() (0x004BF4A0, ILocomotion 23)
// A moving aircraft starts drifting (a random 20..30, either way) and stops.
#include "shared/fly_locomotion.hpp"
// @ref ?unknown_id_source_a3d290@@3PAVUnknownIDSource@@A=00a3d290
// @ref ??RRandom2Class@@QAEHHH@Z=006388a0
// @ref ?Power_Off@LocomotionClass@@UAG_NXZ=0053d210

bool __stdcall FlyLocomotionClass::Power_Off()
{
    if (Is_Moving()) {
        unknown_53 = true;
        unknown_54 = unknown_id_source_a3d290->Random()(20, 30);
        if (unknown_id_source_a3d290->Random()(0, 99) < 50) {
            unknown_54 = -unknown_54;
        }
        Stop_Moving();
        unknown_58 = 0;
    }
    return LocomotionClass::Power_Off();
}
