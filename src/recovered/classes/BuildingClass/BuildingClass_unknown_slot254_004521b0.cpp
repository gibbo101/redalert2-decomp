// int BuildingClass::unknown_slot254(int arg1) (0x004521B0, slot 254)
// With bit 1 of +0xD8 set, values above 1500 drop by 500 and the others
// rise by 500.
#include "shared/building.hpp"

int BuildingClass::unknown_slot254(int arg1)
{
    if ((FlashCount & 2) == 2) {
        if (arg1 > 1500) {
            return arg1 - 500;
        }
        return arg1 + 500;
    }
    return arg1;
}
