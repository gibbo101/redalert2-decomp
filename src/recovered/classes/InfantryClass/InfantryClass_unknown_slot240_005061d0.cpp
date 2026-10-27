// void InfantryClass::unknown_slot240() (0x005061D0, slot 240)
// Unless slot 212 accepts +0x228 with slot 174's weapon: without +0x234
// asks slot 219 (1, the current coordinate, 0) for one, hands the answer to
// slot 220, and when there is none (and the mission is not 5 and the type is
// not JumpJet) calls slot 261 (0, 1).
#include "shared/infantry.hpp"

void InfantryClass::unknown_slot240()
{
    int weapon = unknown_slot174(0);
    if (unknown_228 != 0 && unknown_slot212(unknown_228, weapon)) {
        return;
    }
    AbstractClass *found = 0;
    if (unknown_234 == 0) {
        CoordStruct coord = Coord;
        found = unknown_slot219(1, &coord, 0);
    }
    unknown_slot220(found);
    if (found == 0 && Mission != 5 && !unknown_slot32()->JumpJet) {
        unknown_slot261(0, 1);
    }
}
