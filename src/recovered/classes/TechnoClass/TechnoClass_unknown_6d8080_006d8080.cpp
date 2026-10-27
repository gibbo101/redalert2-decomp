// bool TechnoClass::unknown_6d8080() (0x006D8080)
// With an active, +0x7D object at +0x3F8: heads for the cell 0x006CF130
// picks near it (slot 260, mission 2) and reports true; an inactive one is
// dropped.
#include "shared/techno.hpp"
#include "shared/gscreen.hpp"
#include "shared/techno_map.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_6cf130@TechnoClass@@QAE?AVCell@@PAVAbstractClass@@@Z=006cf130

bool TechnoClass::unknown_6d8080()
{
    if (unknown_3f8 != 0) {
        if (unknown_3f8->unknown_14_bit0 && ((ObjectClass *)unknown_3f8)->unknown_7d) {
            Cell cell = unknown_6cf130(unknown_3f8);
            if (cell.X != unknown_geometry_k.X || cell.Y != unknown_geometry_k.Y) {
                unknown_slot260((AbstractClass *)&Map[cell], 1);
                unknown_slot116(2, false);
                return true;
            }
        } else {
            unknown_3f8 = 0;
        }
    }
    return false;
}
