// int GaugeClass::Set_Maximum(int value) (0x004D0170, slot 34)
#include "shared/gadget.hpp"

int GaugeClass::Set_Maximum(int value)
{
    if (value != MaxValue) {
        MaxValue = value;
        Flag_To_Redraw();
        return true;
    }
    return false;
}
