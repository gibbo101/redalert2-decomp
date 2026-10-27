// int FootClass::unknown_slot268(UnknownSlot268Arg const *arg) (0x004CD9C0)
// For a kind 0x1D record: unless slot 275 holds, 1 or 2 by whether the first
// reference is set; otherwise records it as the pending order (+0x4B4 = 0x1D)
// with the object of the second reference (+0x4B8, 2) or of the first
// (+0x4BC, 1). Anything else: slot 269 and the kind.
#include "shared/foot.hpp"
// @ref ?Unknown_006B5810@UnknownTarget@@QBEPAVAbstractClass@@XZ=006b5810

int FootClass::unknown_slot268(UnknownSlot268Arg const *arg)
{
    int kind = arg->unknown_0c;
    if (kind == 0x1D) {
        bool second = arg->unknown_13.unknown_4 != 0;
        bool first = arg->unknown_0e.unknown_4 != 0;
        if (!unknown_slot275()) {
            return first ? 1 : 2;
        }
        unknown_4c1 = false;
        unknown_4b4 = 0x1D;
        if (second) {
            unknown_4b8 = arg->unknown_13.Unknown_006B5810();
            return 2;
        }
        if (first) {
            unknown_4bc = arg->unknown_0e.Unknown_006B5810();
            return 1;
        }
        unknown_slot269();
    } else {
        unknown_slot269();
    }
    return kind;
}
