// void ToggleClass::Turn_On() (0x006EB160)
#include "shared/gadget.hpp"

void ToggleClass::Turn_On()
{
    IsOn = true;
    Flag_To_Redraw();
}
