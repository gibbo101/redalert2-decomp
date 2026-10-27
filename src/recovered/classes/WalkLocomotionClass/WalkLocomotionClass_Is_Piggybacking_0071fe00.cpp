// bool __stdcall WalkLocomotionClass::Is_Piggybacking() (0x0071FE00, IPiggyback 7)
#include "shared/walk_locomotion.hpp"

bool __stdcall WalkLocomotionClass::Is_Piggybacking()
{
    return Piggybacker != 0;
}
