// void RadarClass::unknown_slot50() (0x0062F210, slot 50)
// Frees the radar's two shapes when they were loaded rather than retrieved.
#include "shared/radar.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?unknown_shape_ab6350@RadarClass@@2PBXB=00ab6350
// @ref ?unknown_shape_ab6350_allocated@RadarClass@@2_NA=00ab6369
// @ref ?unknown_shape_ab6318@RadarClass@@2PBXB=00ab6318
// @ref ?unknown_shape_ab6318_allocated@RadarClass@@2_NA=00ab6368

void RadarClass::unknown_slot50()
{
    if (unknown_shape_ab6350_allocated) {
        operator delete((void *)unknown_shape_ab6350);
        unknown_shape_ab6350_allocated = false;
    }
    unknown_shape_ab6350 = 0;
    if (unknown_shape_ab6318_allocated) {
        operator delete((void *)unknown_shape_ab6318);
        unknown_shape_ab6318_allocated = false;
    }
    unknown_shape_ab6318 = 0;
}
