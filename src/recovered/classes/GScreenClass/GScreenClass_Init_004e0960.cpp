// void GScreenClass::Init(int theater) (0x004E0960, slot 6)
// Resets the redraw state and the input gadgets.
#include "shared/gscreen.hpp"

void GScreenClass::Init(int theater)
{
    Init_Clear();
    Init_IO();
}
