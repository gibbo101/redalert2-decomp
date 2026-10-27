// void __stdcall DriveLocomotionClass::Force_New_Slope(int ramp) (0x0049FC30, ILocomotion 31)
// Both ramps become ramp and the slope timer restarts.
#include "shared/drive_locomotion.hpp"
// @ref ?Frame@@3HA=00a40d2c

void __stdcall DriveLocomotionClass::Force_New_Slope(int ramp)
{
    unknown_20 = ramp;
    unknown_1c = ramp;
    unknown_24 = UnknownSlopeTimer();
}
