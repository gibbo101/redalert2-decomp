// void EditClass::Set_Focus() (0x004B2F20, slot 20)
// Puts the cursor at the end of the text.
#include "shared/gadget.hpp"
// @ref ?Set_Focus@GadgetClass@@UAEXXZ=004cf5e0

void EditClass::Set_Focus()
{
    Length = 0;
    if (String != 0) {
        Length = wcslen(String);
    }
    GadgetClass::Set_Focus();
}
