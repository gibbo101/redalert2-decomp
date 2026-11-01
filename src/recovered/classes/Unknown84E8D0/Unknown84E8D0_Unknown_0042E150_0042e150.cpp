// Unknown84E8D0::Unknown_0042E150 (0x0042E150): deletes every beacon and disables them.
#include "shared/beacon.hpp"

void Unknown84E8D0::Unknown_0042E150()
{
    if (unknown_60) {
        for (int house = 0; house < 8; house++) {
            for (int slot = 0; slot < 3; slot++) {
                if (unknown_00[house][slot]) {
                    delete unknown_00[house][slot];
                    unknown_00[house][slot] = 0;
                }
            }
        }
        unknown_60 = 0;
    }
}
