// void GScreenClass::Init_Clear() (0x004E0980, slot 7)
// Asks for a complete redraw.
#include "shared/gscreen.hpp"

void GScreenClass::Init_Clear()
{
    IsToRedraw = 2;
}
