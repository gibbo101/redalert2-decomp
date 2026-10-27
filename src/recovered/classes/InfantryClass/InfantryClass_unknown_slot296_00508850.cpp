// void InfantryClass::unknown_slot296() (0x00508850, slot 296)
// Clears +0x5BC unless the type is Fearless.
#include "shared/infantry.hpp"

void InfantryClass::unknown_slot296()
{
    if (!Type->Fearless) {
        unknown_5bc = 0;
    }
}
