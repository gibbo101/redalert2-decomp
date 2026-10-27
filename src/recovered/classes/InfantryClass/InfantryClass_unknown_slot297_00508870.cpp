// void InfantryClass::unknown_slot297(int arg1) (0x00508870, slot 297)
// Slot 311 with action 10 for arg1 1, else 9.
#include "shared/infantry.hpp"

void InfantryClass::unknown_slot297(int arg1)
{
    switch (arg1) {
    case 1:
        unknown_slot311(10, 0, 0);
        break;

    default:
        unknown_slot311(9, 0, 0);
        break;
    }
}
