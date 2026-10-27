// bool __stdcall MechLocomotionClass::Process() (0x00591840, ILocomotion 16)
// One step (0x005919A0), then whether still moving.
#include "shared/mech_locomotion.hpp"
// @ref ?unknown_5919a0@MechLocomotionClass@@QAEX_N@Z=005919a0

bool __stdcall MechLocomotionClass::Process()
{
    unknown_5919a0(true);
    return Is_Moving();
}
