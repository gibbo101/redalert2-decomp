// int GadgetClass::Is_List_To_Redraw() (0x004CF640, slot 23)
// True when any gadget of the list (from this one) needs a redraw.
#include "shared/gadget.hpp"

int GadgetClass::Is_List_To_Redraw()
{
    for (GadgetClass *gadget = this; gadget != 0; gadget = (GadgetClass *)gadget->Get_Next()) {
        if (gadget->IsToRepaint) {
            return true;
        }
    }
    return false;
}
