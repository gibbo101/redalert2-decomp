// void ListClass::Remove_Item(int index) (0x0053A0F0, slot 42)
// Removes an item and keeps the selection and view inside the list.
#include "shared/gadget.hpp"

void ListClass::Remove_Item(int index)
{
    if ((unsigned)index < (unsigned)List.Count()) {
        List.Delete(index);
        if (List.Count() <= LineCount) {
            Remove_Scroll_Bar();
        }
        if (IsScrollActive) {
            ScrollGadget.Set_Maximum(List.Count());
        }
        if (SelectedIndex >= List.Count()) {
            SelectedIndex--;
            if (SelectedIndex < 0) {
                SelectedIndex = 0;
            }
        }
        if (CurrentTopIndex >= List.Count()) {
            CurrentTopIndex--;
            if (CurrentTopIndex < 0) {
                CurrentTopIndex = 0;
            }
            if (IsScrollActive) {
                ScrollGadget.Step(1);
            }
        }
    }
}
