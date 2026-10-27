// int GaugeClass::Pixel_To_Value(int pixel) (0x004D01C0, slot 40)
// The value at a screen coordinate along the gauge (inside the 1-pixel border).
#include "shared/gadget.hpp"

int GaugeClass::Pixel_To_Value(int pixel)
{
    int maximum;
    if (IsHorizontal) {
        pixel -= X + 1;
        maximum = Width;
    } else {
        pixel -= Y + 1;
        maximum = Height;
    }
    maximum -= 2;
    if (pixel < 0) {
        pixel = 0;
    } else if (pixel > maximum) {
        pixel = maximum;
    }
    return (int)((double)pixel / maximum * MaxValue);
}
