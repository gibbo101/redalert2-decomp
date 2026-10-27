// bool UnitClass::unknown_slot78(int arg1, int arg2, bool arg3) (0x006FD5A0, slot 78)
// arg1 is an action, arg2 the object it applies to (hypothesis: Westwood's
// Active_Click_With). Re-derives the action (slot 28); a changed answer of
// 3 becomes 1 and of 9 or 16 becomes 5, as do 27 and 29. Moving onto
// itself (2 or 5) is refused; otherwise the foot behaviour.
#include "shared/unit.hpp"
// @ref ?unknown_slot78@FootClass@@UAE_NHH_N@Z=004c61a0

bool UnitClass::unknown_slot78(int arg1, int arg2, bool arg3)
{
    ObjectClass *object = (ObjectClass *)arg2;
    int action = unknown_slot28(object, arg3);
    if (arg1 != action) {
        arg1 = action;
        switch (action) {
        case 3:
            arg1 = 1;
            break;
        case 9:
        case 16:
            arg1 = 5;
            break;
        }
    }
    if (arg1 == 27 || arg1 == 29) {
        arg1 = 5;
    }
    if (object == this && (arg1 == 2 || arg1 == 5)) {
        return false;
    }
    return FootClass::unknown_slot78(arg1, arg2, arg3);
}
