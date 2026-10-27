// void ListClass::Step(int up) (0x0053A430, slot 49)
#include "shared/gadget.hpp"

void ListClass::Step(int up)
{
    if (IsScrollActive) {
        if (ScrollGadget.Step(up)) {
            CurrentTopIndex = ScrollGadget.Get_Value();
            Flag_To_Redraw();
        }
    }
}
