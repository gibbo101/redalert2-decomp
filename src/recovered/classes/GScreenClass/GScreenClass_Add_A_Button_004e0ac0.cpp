// bool GScreenClass::Add_A_Button(GadgetClass &gadget) (0x004E0AC0, slot 12)
// Appends gadget to the button list (or starts the list with it); false
// when it is already listed.
#include "shared/gscreen.hpp"
// @ref ?Buttons@GScreenClass@@2PAVGadgetClass@@A=00a40eec

bool GScreenClass::Add_A_Button(GadgetClass &gadget)
{
    if (Is_Button_Listed(gadget)) {
        return false;
    }
    if (Buttons != 0) {
        gadget.Add_Tail(*Buttons);
        return true;
    }
    Buttons = &gadget;
    return true;
}
