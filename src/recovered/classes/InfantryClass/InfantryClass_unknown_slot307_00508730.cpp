// void InfantryClass::unknown_slot307() (0x00508730)
// Ends sequences 6, 3 and 0x11.
#include "shared/infantry.hpp"

void InfantryClass::unknown_slot307()
{
    if (Sequence == 6 || Sequence == 3 || Sequence == 0x11) {
        Sequence = -1;
    }
}
