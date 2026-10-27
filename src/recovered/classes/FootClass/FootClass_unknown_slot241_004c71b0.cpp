// CoordStruct FootClass::unknown_slot241() (0x004C71B0)
// Unless the mission is 1, the coordinate (slot 22) of +0x490, else of
// +0x494; otherwise TechnoClass's.
#include "shared/foot.hpp"
// @ref ?unknown_slot241@TechnoClass@@UAE?AUCoordStruct@@XZ=006d13b0

CoordStruct FootClass::unknown_slot241()
{
    if (unknown_slot91() != 1) {
        if (unknown_490 != 0) {
            return unknown_490->unknown_slot22();
        }
        if (unknown_494 != 0) {
            return unknown_494->unknown_slot22();
        }
    }
    return TechnoClass::unknown_slot241();
}
