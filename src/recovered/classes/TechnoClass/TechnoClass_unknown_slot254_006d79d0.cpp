// int TechnoClass::unknown_slot254(int arg1) (0x006D79D0, slot 254)
// With bit 2 of FlashCount: 2000 up to 1500, else 500; otherwise arg1.
#include "shared/techno.hpp"

int TechnoClass::unknown_slot254(int arg1)
{
    if ((FlashCount & 2) == 2) {
        return arg1 > 1500 ? 500 : 2000;
    }
    return arg1;
}
