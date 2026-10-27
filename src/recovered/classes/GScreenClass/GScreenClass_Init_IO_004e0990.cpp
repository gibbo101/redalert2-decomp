// void GScreenClass::Init_IO() (0x004E0990, slot 8)
// Drops the button list.
#include "shared/gscreen.hpp"
// @ref ?Buttons@GScreenClass@@2PAVGadgetClass@@A=00a40eec

void GScreenClass::Init_IO()
{
    Buttons = 0;
}
