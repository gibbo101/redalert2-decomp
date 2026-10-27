// void GadgetClass::Enable() (0x004CF140, slot 16)
#include "shared/gadget.hpp"

void GadgetClass::Enable()
{
    IsDisabled = false;
    IsToRepaint = true;
    Clear_Focus();
}
