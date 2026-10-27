// int InfantryClass::unknown_slot221(int arg1, int arg2) (0x00504F50, slot 221)
// TechnoClass's (after clearing +0x57D); when that is set, a Fraidycat
// without ammunition and not +0x76 starts fearing (+0x5BC 300) and leaves
// missions 1 and 15 for 5.
#include "shared/infantry.hpp"
// @ref ?unknown_slot221@TechnoClass@@UAEHHH@Z=006ca890

int InfantryClass::unknown_slot221(int arg1, int arg2)
{
    unknown_57d = false;
    int result = TechnoClass::unknown_slot221(arg1, arg2);
    if (result != 0 && !unknown_76 && Type->Fraidycat && unknown_254 == 0) {
        unknown_5bc = 300;
        if (unknown_slot91() == 1 || unknown_slot91() == 15) {
            unknown_slot116(5, false);
        }
    }
    return result;
}
