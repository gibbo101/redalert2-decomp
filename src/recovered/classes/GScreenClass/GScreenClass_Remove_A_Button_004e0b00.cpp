// bool GScreenClass::Remove_A_Button(GadgetClass &gadget) (0x004E0B00, slot 13)
// Unlinks a listed gadget; the list continues at what Remove returns.
#include "shared/gscreen.hpp"
// @ref ?Buttons@GScreenClass@@2PAVGadgetClass@@A=00a40eec

bool GScreenClass::Remove_A_Button(GadgetClass &gadget)
{
    if (!Is_Button_Listed(gadget)) {
        return false;
    }
    Buttons = (GadgetClass *)gadget.Remove();
    return true;
}
