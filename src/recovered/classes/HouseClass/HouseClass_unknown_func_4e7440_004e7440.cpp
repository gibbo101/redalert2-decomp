// bool HouseClass::unknown_func_4e7440(int type) (0x004E7440)
// Whether any house that is not an ally counts one or more of a type
// (its +0x5460 counter).
#include "shared/techno.hpp"

bool HouseClass::unknown_func_4e7440(int type)
{
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *house = Houses[index];
        if (house != 0 && !Is_Ally(house) && house->unknown_5460.unknown_func_491d10(type) > 0) {
            return true;
        }
    }
    return false;
}
