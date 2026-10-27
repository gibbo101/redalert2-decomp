// HouseClass *__fastcall HouseClass::As_Pointer(int type) (0x004ED760)
// The house whose type has this index, or 0.
#include "shared/techno.hpp"

HouseClass *__fastcall HouseClass::As_Pointer(int type)
{
    for (int index = 0; index < Houses.Count(); index++) {
        HouseClass *house = Houses[index];
        if (house->Type->House == type) {
            return house;
        }
    }
    return 0;
}
