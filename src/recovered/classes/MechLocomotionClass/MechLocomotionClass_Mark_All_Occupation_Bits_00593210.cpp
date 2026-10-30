// void __stdcall MechLocomotionClass::Mark_All_Occupation_Bits(int mark) (ILocomotion 39)
// Lifting the mark (0) clears the occupation of the head-to coordinate (object slot 59).
#include "shared/mech_locomotion.hpp"
#include "shared/foot.hpp"

void __stdcall MechLocomotionClass::Mark_All_Occupation_Bits(int mark)
{
    if (mark == 0) {
        UnknownCoord434820 coord = Head_To_Coord();
        LinkedTo->unknown_slot59(coord);
    }
}
