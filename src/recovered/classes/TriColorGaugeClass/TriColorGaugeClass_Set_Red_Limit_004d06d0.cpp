// int TriColorGaugeClass::Set_Red_Limit(int value) (0x004D06D0, slot 42)
#include "shared/gadget.hpp"

int TriColorGaugeClass::Set_Red_Limit(int value)
{
    if (value >= 0 && value < MaxValue) {
        RedLimit = value;
        Flag_To_Redraw();
        return true;
    }
    return false;
}
