// int TriColorGaugeClass::Set_Yellow_Limit(int value) (0x004D0700, slot 43)
#include "shared/gadget.hpp"

int TriColorGaugeClass::Set_Yellow_Limit(int value)
{
    if (value >= 0 && value < MaxValue) {
        YellowLimit = value;
        Flag_To_Redraw();
        return true;
    }
    return false;
}
