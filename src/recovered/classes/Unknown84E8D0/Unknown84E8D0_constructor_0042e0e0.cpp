// Unknown84E8D0::Unknown84E8D0 (0x0042E0E0): no beacons, disabled, no radar blink cycle. Out of line
// here; the definition of unknown_object_84e8d0 (0x0042D960) expands it.
#include "shared/beacon.hpp"

Unknown84E8D0::Unknown84E8D0()
{
    for (int house = 0; house < 8; house++) {
        for (int slot = 0; slot < 3; slot++) {
            unknown_00[house][slot] = 0;
        }
    }
    unknown_60 = 0;
    unknown_7c = 0;
}
