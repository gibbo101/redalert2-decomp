// bool __stdcall WalkLocomotionClass::Process() (0x0071DFF0, ILocomotion 16)
// One step (0x0071E220) under the processing flag, then whether moving.
#include "shared/walk_locomotion.hpp"
// @ref ?unknown_71e220@WalkLocomotionClass@@QAEX_N@Z=0071e220

bool __stdcall WalkLocomotionClass::Process()
{
    unknown_35 = true;
    unknown_71e220(true);
    unknown_35 = false;
    return Is_Moving();
}
