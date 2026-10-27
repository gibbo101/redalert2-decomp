// int GaugeClass::Set_Value(int value) (0x004D0190, slot 35)
// Clamps value to 0..MaxValue.
#include "shared/gadget.hpp"

int GaugeClass::Set_Value(int value)
{
    int maximum = MaxValue;
    if (value < 0) {
        value = 0;
    } else if (value > maximum) {
        value = maximum;
    }
    if (value != CurValue) {
        CurValue = value;
        Flag_To_Redraw();
        return true;
    }
    return false;
}
