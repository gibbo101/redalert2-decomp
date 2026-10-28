// int ShipLocomotionClass::Is_Level() (0x00675F80)
// The slope change has finished and the hull is level (both tilt angles
// under 0.005).
#include "shared/ship_locomotion.hpp"
#include "shared/crt_math.hpp"
// @ref __real@8@3fff8000000000000000=0079a708
// @ref __real@8@3ff7a3d70a3d70a3d800=0079d170

int ShipLocomotionClass::Is_Level()
{
    float ratio = Slope_Ratio();
    if (ratio == 1.0 && fabs(LinkedTo->unknown_280) < 0.005 && fabs(LinkedTo->unknown_284) < 0.005) {
        return true;
    }
    return false;
}
