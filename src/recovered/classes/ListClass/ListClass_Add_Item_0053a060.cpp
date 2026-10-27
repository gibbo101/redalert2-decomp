// int ListClass::Add_Item(wchar_t *text) (0x0053A060, slot 34)
// Appends text (null is ignored); returns the index of the last item.
#include "shared/gadget.hpp"

int ListClass::Add_Item(wchar_t *text)
{
    if (text != 0) {
        List.Add(text);
        Flag_To_Redraw();
        if (List.Count() > LineCount) {
            Add_Scroll_Bar();
        }
        if (IsScrollActive) {
            ScrollGadget.Set_Maximum(List.Count());
        }
    }
    return List.Count() - 1;
}
