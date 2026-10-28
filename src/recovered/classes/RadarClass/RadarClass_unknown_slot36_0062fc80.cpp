// bool RadarClass::unknown_slot36(Cell const &cell, HouseClass *house) (0x0062FC80)
// Passes the call on (the radar adds nothing).
#include "shared/radar.hpp"
// @ref ?unknown_slot36@DisplayClass@@UAE_NABVCell@@PAVHouseClass@@@Z=00499bb0

bool RadarClass::unknown_slot36(Cell const &cell, HouseClass *house)
{
    if (DisplayClass::unknown_slot36(cell, house)) {
        return true;
    }
    return false;
}
