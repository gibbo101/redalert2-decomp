// bool __stdcall HoverLocomotionClass::Shove(UnknownFacingDir dir) (0x004FEBD0, ILocomotion 27)
// A successful push also starts a drift.
#include "shared/hover_locomotion.hpp"

bool __stdcall HoverLocomotionClass::Shove(UnknownFacingDir dir)
{
    if (Push(dir)) {
        Start_Drift();
        return true;
    }
    return false;
}
