// void GadgetClass::Set_Focus() (0x004CF5E0, slot 20)
// Takes the keyboard focus from the gadget that had it.
#include "shared/gadget.hpp"

void GadgetClass::Set_Focus()
{
    if (Focused != 0) {
        Focused->Flag_To_Redraw();
        Focused->Clear_Focus();
    }
    Flags |= KEYBOARD;
    Focused = this;
}
