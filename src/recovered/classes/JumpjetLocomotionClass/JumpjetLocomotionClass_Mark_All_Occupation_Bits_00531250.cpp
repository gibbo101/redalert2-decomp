// void __stdcall JumpjetLocomotionClass::Mark_All_Occupation_Bits(int mark) (0x00531250, ILocomotion 39)
// When clearing (mark 0) with a head-to coordinate, while idle (+0x4C 0) or
// still marked (+0x88), unmarks the head-to cell (slot 59) and clears +0x88.
// The head-to copy is an UnknownCoord434820 (its forwarding constructor makes
// VC6 copy all three words before the comparison, as the original does).
#include "shared/jumpjet_locomotion.hpp"

void __stdcall JumpjetLocomotionClass::Mark_All_Occupation_Bits(int mark)
{
    if (mark == 0) {
        UnknownCoord434820 head = Head_To_Coord();
        if (head != unknown_coord_a6e3e0 && (unknown_4c == 0 || unknown_88)) {
            LinkedTo->unknown_slot59(head);
            unknown_88 = false;
        }
    }
}
