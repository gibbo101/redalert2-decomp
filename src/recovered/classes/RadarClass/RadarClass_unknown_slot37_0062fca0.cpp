// bool RadarClass::unknown_slot37(Cell const &cell, int arg2, bool arg3) (0x0062FCA0)
// Passes the call on (the radar adds nothing).
#include "shared/radar.hpp"
// @ref ?unknown_slot37@DisplayClass@@UAE_NABVCell@@H_N@Z=00499fc0

bool RadarClass::unknown_slot37(Cell const &cell, int arg2, bool arg3)
{
    if (DisplayClass::unknown_slot37(cell, arg2, arg3)) {
        return true;
    }
    return false;
}
