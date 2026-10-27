// int TechnoClass::unknown_slot254(int arg1) (0x006D79D0, slot 254)
// With bit 2 of unknown_d8: 2000 up to 1500, else 500; otherwise arg1.
#include "shared/techno.hpp"

int TechnoClass::unknown_slot254(int arg1)
{
    if ((unknown_d8 & 2) == 2) {
        return arg1 > 1500 ? 500 : 2000;
    }
    return arg1;
}
