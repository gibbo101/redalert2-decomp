// void ListClass::Bump(int up) (0x0053A3E0, slot 36)
#include "shared/gadget.hpp"

void ListClass::Bump(int up)
{
    if (IsScrollActive) {
        if (ScrollGadget.Step(up)) {
            CurrentTopIndex = ScrollGadget.Get_Value();
            Flag_To_Redraw();
        }
    }
}
