// LaserDrawClass: a laser line drawn for a time (0x58 bytes; name from the
// RTTI of VectorClass<LaserDrawClass *> 0x007A5434; every live laser is in
// the list LaserDrawClass_list_init 0x00533070 constructs). The constructor
// argument names are hypotheses (public YR references); TechnoClass
// 0x006C9DF0 is the caller recovered here.
#ifndef RA2_SHARED_LASER_DRAW_HPP
#define RA2_SHARED_LASER_DRAW_HPP

#include "shared/coord.hpp"
#include "shared/rgb_class.hpp"

class LaserDrawClass {
public:
    LaserDrawClass(CoordStruct source, CoordStruct target, int z_adjust, bool unknown, RGBClass inner, RGBClass outer,
                   RGBClass outer_spread, int duration, bool blinks, bool fades, float start_intensity,
                   float end_intensity);       // 0x00533110
    char unknown_00[0x1C];
    bool IsHouseColor;                          // +0x1C (drawn in the owner's colour)
    char unknown_1d[0x58 - 0x1D];
};

#endif
