// bool RadarClass::unknown_slot36(Cell const &cell, int arg2) (0x0062FC80)
// Passes the call on (the radar adds nothing).
#include "shared/radar.hpp"
// @ref ?unknown_slot36@DisplayClass@@UAE_NABVCell@@H@Z=00499bb0

bool RadarClass::unknown_slot36(Cell const &cell, int arg2)
{
    if (DisplayClass::unknown_slot36(cell, arg2)) {
        return true;
    }
    return false;
}
