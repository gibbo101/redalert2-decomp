// bool GScreenClass::Is_Button_Listed(GadgetClass &gadget) (0x004E0AA0, slot 11)
// The gadget is in the button list when the list starts at Buttons.
#include "shared/gscreen.hpp"
// @ref ?Buttons@GScreenClass@@2PAVGadgetClass@@A=00a40eec

bool GScreenClass::Is_Button_Listed(GadgetClass &gadget)
{
    return Buttons == &gadget.Head_Of_List();
}
