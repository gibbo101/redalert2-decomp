// void GaugeClass::Draw_Thumb() (0x004D0580, slot 39)
// A raised box four pixels long at the current value, kept inside the gauge.
#include "shared/gadget.hpp"
#include "shared/text_print.hpp"
// @ref ?Draw_Box@@YIXABVRect@@H_N@Z=004973d0

void GaugeClass::Draw_Thumb()
{
    int x = Value_To_Pixel(CurValue);
    if (x + 4 > Value_To_Pixel(MaxValue)) {
        x = Value_To_Pixel(MaxValue) - 2;
    }
    if (x < X) {
        x = X;
    }
    if (IsHorizontal) {
        Draw_Box(Rect(x, Y, 4, Height), 1, true);
    } else {
        Draw_Box(Rect(X, x, Width, 4), 1, true);
    }
}
