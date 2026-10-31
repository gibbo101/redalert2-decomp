// void TechnoClass::unknown_slot79(int arg1) (0x006C7440, slot 79)
// Stores FlashCount unless slot 49 holds and slot 51 is 0.
#include "shared/techno.hpp"
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

void TechnoClass::unknown_slot79(int arg1)
{
    if (!unknown_slot49(unknown_player_a35db4) || unknown_slot51(1)) {
        FlashCount = arg1;
    }
}
