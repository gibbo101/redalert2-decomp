// void ShipLocomotionClass::Set_Slope(int ramp) (0x00675BB0)
// A different ramp starts a three-frame change from the current one.
#include "shared/ship_locomotion.hpp"

void ShipLocomotionClass::Set_Slope(int ramp)
{
    if (ramp != unknown_1c) {
        unknown_20 = unknown_1c;
        unknown_1c = ramp;
        unknown_24 = UnknownSlopeTimer(3);
    }
}
