// bool TerrainClass::unknown_slot71(int arg1) (0x006E37E0)
// After the base handling succeeds, takes the object off its cell (mode 0)
// or puts it on the cell (modes 1 and 3).
#include "shared/terrain.hpp"
// @ref ?unknown_slot71@ObjectClass@@UAE_NH@Z=005d4160
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_0054AB70@MapClass@@QAEXABVCell@@PAVObjectClass@@@Z=0054ab70
// @ref ?Unknown_0054AF70@MapClass@@QAEXABVCell@@PAVObjectClass@@@Z=0054af70

bool TerrainClass::unknown_slot71(int arg1)
{
    if (ObjectClass::unknown_slot71(arg1)) {
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
        return true;
    }
    return false;
}
