// int GadgetClass::Draw_Me(int forced) (0x004CF240, slot 27)
// True (and clears the redraw flag) when the gadget should be drawn.
#include "shared/gadget.hpp"

int GadgetClass::Draw_Me(int forced)
{
    if (forced || IsToRepaint) {
        IsToRepaint = false;
        return true;
    }
    return false;
}
