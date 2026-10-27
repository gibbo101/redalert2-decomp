// void GadgetClass::Disable() (0x004CF150, slot 15)
#include "shared/gadget.hpp"

void GadgetClass::Disable()
{
    IsDisabled = true;
    IsToRepaint = true;
    Clear_Focus();
}
