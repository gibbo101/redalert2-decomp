// bool Unknown84E8D0::Unknown_0042E700(int house) (0x0042E700)
// Whether the house still has an empty one of its three slots (DisplayClass
// 0x0049CAC0 tests it before entering the +0x11B0 mode).
#include "shared/unknown_globals.hpp"

bool Unknown84E8D0::Unknown_0042E700(int house)
{
    for (int i = 0; i < 3; i++) {
        if (unknown_00[house][i] == 0) {
            return true;
        }
    }
    return false;
}
