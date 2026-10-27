// void ListClass::Flag_To_Redraw() (0x0053A990, slot 18)
#include "shared/gadget.hpp"
// @ref ?Flag_To_Redraw@GadgetClass@@UAEXXZ=004cf5a0

void ListClass::Flag_To_Redraw()
{
    if (IsScrollActive) {
        UpGadget.Flag_To_Redraw();
        DownGadget.Flag_To_Redraw();
        ScrollGadget.Flag_To_Redraw();
    }
    ControlClass::Flag_To_Redraw();
}
