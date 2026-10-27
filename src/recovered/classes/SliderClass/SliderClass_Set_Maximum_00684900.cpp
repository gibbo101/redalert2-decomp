// int SliderClass::Set_Maximum(int value) (0x00684900, slot 34)
#include "shared/gadget.hpp"
// @ref ?Set_Maximum@GaugeClass@@UAEHH@Z=004d0170

int SliderClass::Set_Maximum(int value)
{
    if (GaugeClass::Set_Maximum(value)) {
        Recalc_Thumb();
        return true;
    }
    return false;
}
