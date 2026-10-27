// int GaugeClass::Value_To_Pixel(int value) (0x004D0240, slot 41)
// The screen coordinate of a value along the gauge.
#include "shared/gadget.hpp"

int GaugeClass::Value_To_Pixel(int value)
{
    int start;
    int maximum;
    if (IsHorizontal) {
        maximum = Width;
        start = X;
    } else {
        maximum = Height;
        start = Y;
    }
    maximum -= 2;
    return (int)((double)value / MaxValue * maximum + start);
}
