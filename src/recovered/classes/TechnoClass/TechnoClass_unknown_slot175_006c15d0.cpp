// int TechnoClass::unknown_slot175(ObjectClass *target) (0x006C15D0, slot 175)
// How the techno may target an active object by its type's NavalTargeting
// (-1 never, 0/1 by whether the target is Underwater, Organic or hovering).
// Body 256 bytes: code to 0x006C16B3 and the seven-entry jump table at
// 0x006C16B4. Case 0 returns its 0 itself (not through the shared final
// return): only then is case 6's `return -1` cross-jumped into the guard's
// return block (+0x14), as in the original, instead of case 0's (+0x84).
#include "shared/techno.hpp"

int TechnoClass::unknown_slot175(ObjectClass *target)
{
    bool active = target != 0 && target->unknown_14_bit0;
    if (!active) {
        return -1;
    }
    bool underwater = target->unknown_slot32()->Underwater;
    bool organic = target->unknown_slot32()->Organic;
    bool hover = target->unknown_slot32()->SpeedType == 3;
    switch (unknown_slot32()->NavalTargeting) {
    case 0:
        if (underwater && ((TechnoClass *)target)->unknown_1b8 != 0) {
            return -1;
        }
        return 0;
    case 1:
        return underwater ? 1 : 0;
    case 2:
        return underwater ? 0 : -1;
    case 3:
        return organic ? 1 : 0;
    case 4:
        if (!hover && !organic) {
            return 1;
        }
        break;
    case 5:
        break;
    case 6:
        return -1;
    }
    return 0;
}
