// int ListClass::Add_Scroll_Bar() (0x0053A5A0, slot 35)
// Narrows the list and links the arrows and scroll bar in after it.
#include "shared/gadget.hpp"

int ListClass::Add_Scroll_Bar()
{
    if (!IsScrollActive) {
        IsScrollActive = true;
        Flag_To_Redraw();
        Width -= ScrollGadget.Width;
        UpGadget.Make_Peer(*this);
        DownGadget.Make_Peer(*this);
        ScrollGadget.Make_Peer(*this);
        UpGadget.Add(*this);
        DownGadget.Add(*this);
        ScrollGadget.Add(*this);
        UpGadget.Flag_To_Redraw();
        DownGadget.Flag_To_Redraw();
        ScrollGadget.Flag_To_Redraw();
        ScrollGadget.Set_Maximum(List.Count());
        ScrollGadget.Set_Thumb_Size(LineCount);
        ScrollGadget.Set_Value(CurrentTopIndex);
        return true;
    }
    return false;
}
