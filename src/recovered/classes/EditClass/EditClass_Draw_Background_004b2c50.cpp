// void EditClass::Draw_Background() (0x004B2C50, slot 36)
// An outlined box (style 4), filled.
#include "shared/gadget.hpp"
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

void EditClass::Draw_Background()
{
    Draw_Box(Rect(X, Y, Width, Height), 4, true);
}
