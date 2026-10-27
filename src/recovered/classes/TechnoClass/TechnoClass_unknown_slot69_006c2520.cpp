// void TechnoClass::unknown_slot69() (0x006C2520, slot 69)
// Clears unknown_373 when the owner test 0x004F52F0 fails.
#include "shared/techno.hpp"
// @ref ?Unknown_004F52F0@HouseClass@@QAE_NXZ=004f52f0

void TechnoClass::unknown_slot69()
{
    if (unknown_373) {
        if (!House->Unknown_004F52F0()) {
            unknown_373 = false;
        }
    }
}
