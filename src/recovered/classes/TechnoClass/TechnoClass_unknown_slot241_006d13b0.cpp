// CoordStruct TechnoClass::unknown_slot241() (0x006D13B0, slot 241)
// With mission 1 and a +0x228 object, its slot 22 coordinate; otherwise Coord.
#include "shared/techno.hpp"

CoordStruct TechnoClass::unknown_slot241()
{
    if (unknown_slot91() == 1 && unknown_228) {
        return unknown_228->unknown_slot22();
    }
    return Coord;
}
