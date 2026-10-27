// bool HouseClass::unknown_func_4e90c0(int arg1) (0x004E90C0)
// For 4 with buildings left: sells every building and sends every unit to
// hunt (through the IHouse slots).
#include "shared/techno.hpp"

bool HouseClass::unknown_func_4e90c0(int arg1)
{
    if (CurBuildings > 0 && arg1 == 4) {
        Fire_Sale();
        All_To_Hunt();
        return true;
    }
    return false;
}
