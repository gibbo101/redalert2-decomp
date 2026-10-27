// int SliderClass::Set_Value(int value) (0x00684A10, slot 35)
// The value is kept within MaxValue - Thumb.
#include "shared/gadget.hpp"
// @ref ?Set_Value@GaugeClass@@UAEHH@Z=004d0190

int SliderClass::Set_Value(int value)
{
    int maximum = MaxValue - Thumb;
    if (value >= maximum) {
        value = maximum;
    }
    if (GaugeClass::Set_Value(value)) {
        Recalc_Thumb();
        return true;
    }
    return false;
}
