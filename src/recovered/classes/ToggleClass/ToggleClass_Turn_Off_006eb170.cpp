// void ToggleClass::Turn_Off() (0x006EB170)
#include "shared/gadget.hpp"

void ToggleClass::Turn_Off()
{
    IsOn = false;
    Flag_To_Redraw();
}
