// void __stdcall ShipLocomotionClass::Force_New_Slope(int ramp) (0x00675BF0, ILocomotion 31)
// Both ramps become ramp and the slope timer restarts.
#include "shared/ship_locomotion.hpp"
// @ref ?Frame@@3HA=00a40d2c

void __stdcall ShipLocomotionClass::Force_New_Slope(int ramp)
{
    unknown_20 = ramp;
    unknown_1c = ramp;
    unknown_24 = UnknownSlopeTimer();
}
