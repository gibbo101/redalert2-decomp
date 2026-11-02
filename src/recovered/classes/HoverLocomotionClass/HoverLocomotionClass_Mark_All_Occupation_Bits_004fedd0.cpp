#include "shared/hover_locomotion.hpp"
void __stdcall HoverLocomotionClass::Mark_All_Occupation_Bits(int mark)
{
    if (mark==0) {
        UnknownCoord434820 coord=Head_To_Coord();
        LinkedTo->unknown_slot59(coord);
    }
}
