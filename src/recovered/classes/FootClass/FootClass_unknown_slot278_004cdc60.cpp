// void FootClass::unknown_slot278() (0x004CDC60)
// Resumes a pending order: keeps attacking the current target (slot 215)
// while that still works, otherwise heads for the unit's coordinate (slot
// 209) and on success enters mission 1 and marks the order resumed (+0x4C1).
#include "shared/foot.hpp"

void FootClass::unknown_slot278()
{
    if (unknown_4b8 != 0) {
        if (unknown_4c1) {
            if (unknown_slot215(unknown_228)) {
                return;
            }
            unknown_228 = 0;
        }
        CoordStruct coord = Coord;
        if (unknown_slot209(&coord, 1)) {
            unknown_slot116(1, true);
            unknown_4c1 = true;
        }
    } else {
        if (unknown_4bc != 0 && unknown_slot215(unknown_4bc)) {
            return;
        }
        if (unknown_4c1 && unknown_slot215(unknown_228)) {
            return;
        }
        unknown_228 = 0;
        CoordStruct coord = Coord;
        if (unknown_slot209(&coord, 1)) {
            unknown_slot116(1, true);
            unknown_4c1 = true;
        } else {
            unknown_228 = unknown_4bc;
        }
    }
}
