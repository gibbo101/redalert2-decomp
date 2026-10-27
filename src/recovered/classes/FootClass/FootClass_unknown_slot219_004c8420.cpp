// AbstractClass *FootClass::unknown_slot219(int arg1, CoordStruct const *coord, bool arg3) (0x004C8420)
// TechnoClass's, with flag bit 0 forced and bit 1 cleared while
// unknown_578 is set; a zero result clears unknown_578.
#include "shared/foot.hpp"
// @ref ?unknown_slot219@TechnoClass@@UAEHHHH@Z=006c6530

AbstractClass *FootClass::unknown_slot219(int arg1, CoordStruct const *coord, bool arg3)
{
    if (unknown_578) {
        arg1 = (arg1 & ~2) | 1;
    }
    AbstractClass *result = TechnoClass::unknown_slot219(arg1, coord, arg3);
    if (unknown_578 && result == 0) {
        unknown_578 = false;
    }
    return result;
}
