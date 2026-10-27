// void ListClass::Set_Selected_Index(int index) (0x0053A900, slot 46)
// Selects an item and scrolls it into view (invalid indices select 0).
#include "shared/gadget.hpp"

void ListClass::Set_Selected_Index(int index)
{
    if ((unsigned)index < (unsigned)List.Count()) {
        SelectedIndex = index;
        Flag_To_Redraw();
        if (SelectedIndex < CurrentTopIndex) {
            Set_View_Index(SelectedIndex);
        }
        if (SelectedIndex >= CurrentTopIndex + LineCount) {
            Set_View_Index(SelectedIndex - LineCount + 1);
        }
    } else {
        SelectedIndex = 0;
    }
}
