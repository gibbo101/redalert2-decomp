// void InfantryClass::unknown_slot308() (0x00508750)
// Clears +0x5CC and starts sequence 0x1B (slot 311).
#include "shared/infantry.hpp"

void InfantryClass::unknown_slot308()
{
    if (unknown_5cc) {
        unknown_5cc = false;
        unknown_slot311(0x1B, 0, 0);
    }
}
