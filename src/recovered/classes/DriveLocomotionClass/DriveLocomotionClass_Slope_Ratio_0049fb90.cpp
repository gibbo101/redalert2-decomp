// double DriveLocomotionClass::Slope_Ratio() (0x0049FB90)
// How far the slope change has run (1.0 when it has no duration).
#include "shared/drive_locomotion.hpp"
// @ref __real@8@3fff8000000000000000=0079a708

double DriveLocomotionClass::Slope_Ratio()
{
    if (unknown_24.unknown_0c == 0) {
        return 1.0;
    }
    return (double)(unknown_24.unknown_0c - unknown_24.Timer.Value()) / unknown_24.unknown_0c;
}
