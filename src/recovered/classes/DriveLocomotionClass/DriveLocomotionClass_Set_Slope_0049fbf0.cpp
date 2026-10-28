// void DriveLocomotionClass::Set_Slope(int ramp) (0x0049FBF0)
// A different ramp starts a three-frame change from the current one.
#include "shared/drive_locomotion.hpp"

void DriveLocomotionClass::Set_Slope(int ramp)
{
    if (ramp != unknown_1c) {
        unknown_20 = unknown_1c;
        unknown_1c = ramp;
        unknown_24 = UnknownSlopeTimer(3);
    }
}
