// bool __stdcall ShipLocomotionClass::Is_Piggybacking() (0x0067AB60, IPiggyback 7)
#include "shared/ship_locomotion.hpp"

bool __stdcall ShipLocomotionClass::Is_Piggybacking()
{
    return Piggybacker != 0;
}
