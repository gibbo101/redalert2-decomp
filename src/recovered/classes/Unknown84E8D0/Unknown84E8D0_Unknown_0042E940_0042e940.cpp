// Unknown84E8D0::Unknown_0042E940 (0x0042E940): the house's beacon whose text is being edited
// (flag 2; house -1: any house's), else none.
#include "shared/beacon.hpp"

UnknownBeacon *Unknown84E8D0::Unknown_0042E940(int house)
{
    if (unknown_60) {
        for (int index = 0; index < 8; index++) {
            for (int slot = 0; slot < 3; slot++) {
                UnknownBeacon *beacon = unknown_00[index][slot];
                if (beacon && (beacon->unknown_flags & 2)) {
                    if (house == -1) {
                        return beacon;
                    }
                    if (house == beacon->unknown_house) {
                        return beacon;
                    }
                }
            }
        }
    }
    return 0;
}
