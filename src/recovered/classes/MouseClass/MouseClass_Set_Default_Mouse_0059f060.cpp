// void MouseClass::Set_Default_Mouse(int mouse, bool wsmall) (0x0059F060, slot 18)
// Remembers mouse as the normal shape and shows it.
#include "shared/mouse_class.hpp"

void MouseClass::Set_Default_Mouse(int mouse, bool wsmall)
{
    NormalMouseShape = mouse;
    Override_Mouse_Shape(mouse, wsmall);
}
