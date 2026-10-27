// int ListClass::Remove_Scroll_Bar() (0x0053A670, slot 44)
#include "shared/gadget.hpp"

int ListClass::Remove_Scroll_Bar()
{
    if (IsScrollActive) {
        Width += ScrollGadget.Width;
        IsScrollActive = false;
        ScrollGadget.Remove();
        UpGadget.Remove();
        DownGadget.Remove();
        Flag_To_Redraw();
        return true;
    }
    return false;
}
