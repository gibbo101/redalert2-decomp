// bool __stdcall RocketLocomotionClass::Is_Moving() (0x0063DB50, ILocomotion 4)
// A destination is set.
#include "shared/rocket_locomotion.hpp"
// @ref ?unknown_coord_ab6888@@3UCoordStruct@@A=00ab6888

bool __stdcall RocketLocomotionClass::Is_Moving()
{
    return unknown_18 != unknown_coord_ab6888;
}
