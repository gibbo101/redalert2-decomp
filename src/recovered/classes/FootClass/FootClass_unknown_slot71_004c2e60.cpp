// bool FootClass::unknown_slot71(int arg1) (0x004C2E60)
// Mode 2 always succeeds; otherwise TechnoClass's slot 71, and in layer 2
// the map is told about the object at its cell (0x0054AF70 for mode 0,
// 0x0054AB70 for modes 1 and 3).
#include "shared/foot.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054AB70@MapClass@@QAEXABVCell@@PAVObjectClass@@@Z=0054ab70
// @ref ?Unknown_0054AF70@MapClass@@QAEXABVCell@@PAVObjectClass@@@Z=0054af70
// @ref ?unknown_slot71@TechnoClass@@UAE_NH@Z=006c2550

bool FootClass::unknown_slot71(int arg1)
{
    if (arg1 == 2) {
        return true;
    }
    if (TechnoClass::unknown_slot71(arg1)) {
        if (unknown_slot29() == 2) {
            Cell cell = unknown_slot104();
            switch (arg1) {
            case 0:
                Map.Unknown_0054AF70(cell, this);
                break;
            case 1:
            case 3:
                Map.Unknown_0054AB70(cell, this);
                return true;
            }
        }
        return true;
    }
    return false;
}
