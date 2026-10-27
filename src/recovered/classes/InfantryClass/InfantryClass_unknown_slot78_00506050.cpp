// bool InfantryClass::unknown_slot78(int arg1, int arg2, bool arg3) (0x00506050, slot 78)
// Slot 28's action against arg2, with 9, 28 and 29 handled as 9 and 27 and
// 57 as 5; acting on itself with 5 is refused; FootClass's slot 78 with the
// action in place of arg1.
#include "shared/infantry.hpp"
// @ref ?unknown_slot78@FootClass@@UAE_NHH_N@Z=004c61a0

bool InfantryClass::unknown_slot78(int arg1, int arg2, bool arg3)
{
    int action = unknown_slot28((ObjectClass *)arg2, arg3);
    switch (action) {
    case 1:
    case 5:
    case 16:
    case 26:
        action = action;
        break;

    case 9:
    case 28:
    case 29:
        action = 9;
        break;

    case 27:
    case 57:
        action = 5;
        break;
    }
    if ((ObjectClass *)arg2 == this && action == 5) {
        return false;
    }
    return FootClass::unknown_slot78(action, arg2, arg3);
}
