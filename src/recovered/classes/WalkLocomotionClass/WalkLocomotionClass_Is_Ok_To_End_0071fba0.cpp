// bool __stdcall WalkLocomotionClass::Is_Ok_To_End() (0x0071FBA0, IPiggyback 5)
// Once stopped (and not processing) while carrying a locomotor.
#include "shared/walk_locomotion.hpp"

bool __stdcall WalkLocomotionClass::Is_Ok_To_End()
{
    if (!Is_Moving() && Piggybacker != 0 && !unknown_35) {
        return true;
    }
    return false;
}
