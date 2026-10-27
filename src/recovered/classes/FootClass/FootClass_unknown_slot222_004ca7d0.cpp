// bool FootClass::unknown_slot222(HouseClass *house, int arg2) (0x004CA7D0)
// TechnoClass's slot 222 (always with true); on success, unless slot 21
// holds, records the cell of slot 104 at +0x454.
#include "shared/foot.hpp"
// @ref ?unknown_slot222@TechnoClass@@UAE_NPAVHouseClass@@H@Z=006cd940

bool FootClass::unknown_slot222(HouseClass *house, int arg2)
{
    if (TechnoClass::unknown_slot222(house, true)) {
        if (!unknown_slot21()) {
            unknown_454 = unknown_slot104();
        }
        return true;
    }
    return false;
}
