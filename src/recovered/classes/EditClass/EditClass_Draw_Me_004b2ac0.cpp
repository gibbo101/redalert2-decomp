// int EditClass::Draw_Me(int forced) (0x004B2AC0, slot 27)
// Draws the field with the mouse hidden over it.
#include "shared/gadget.hpp"
#include "shared/mouse.hpp"
// @ref ?Draw_Me@ControlClass@@UAEHH@Z=00483530
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

int EditClass::Draw_Me(int forced)
{
    if (ControlClass::Draw_Me(forced)) {
        WWMouse->Conditional_Hide_Mouse(Rect(X, Y, Width, Height));
        Draw_Background();
        Draw_Text(String);
        WWMouse->Conditional_Show_Mouse();
        return true;
    }
    return false;
}
