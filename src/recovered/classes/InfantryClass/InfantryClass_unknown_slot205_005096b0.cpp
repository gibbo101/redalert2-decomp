// void InfantryClass::unknown_slot205() (0x005096B0, slot 205)
// Slot 311 with action 32 while slot 204 holds.
#include "shared/infantry.hpp"

void InfantryClass::unknown_slot205()
{
    if (unknown_slot204()) {
        unknown_slot311(32, 0, 0);
    }
}
