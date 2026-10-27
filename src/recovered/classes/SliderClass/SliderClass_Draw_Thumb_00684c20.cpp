// void SliderClass::Draw_Thumb() (0x00684C20, slot 39)
#include "shared/gadget.hpp"
#include "shared/rect.hpp"
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

void SliderClass::Draw_Thumb()
{
    if (IsHorizontal) {
        Draw_Box(Rect(X + ThumbStart, Y, ThumbSize, Height), 1, true);
    } else {
        Draw_Box(Rect(X, Y + ThumbStart, Width, ThumbSize), 1, true);
    }
}
