// void GadgetClass::Clear_Focus() (0x004CF610, slot 21)
#include "shared/gadget.hpp"

void GadgetClass::Clear_Focus()
{
    if (Focused == this) {
        Flags &= ~KEYBOARD;
        Focused = 0;
    }
}
