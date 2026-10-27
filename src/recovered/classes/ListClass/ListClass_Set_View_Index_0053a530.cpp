// int ListClass::Set_View_Index(int index) (0x0053A530, slot 48)
// Shows the list from item index (clamped so the last page stays full).
#include "shared/gadget.hpp"

int ListClass::Set_View_Index(int index)
{
    int last = List.Count() - LineCount;
    last = (last < 0) ? 0 : last;
    if (index < 0) {
        index = 0;
    } else if (index > last) {
        index = last;
    }
    if (index != CurrentTopIndex) {
        CurrentTopIndex = index;
        Flag_To_Redraw();
        if (IsScrollActive) {
            ScrollGadget.Set_Value(CurrentTopIndex);
        }
        return true;
    }
    return false;
}
