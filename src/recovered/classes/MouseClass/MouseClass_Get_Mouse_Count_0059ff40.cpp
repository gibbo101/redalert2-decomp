// int MouseClass::Get_Mouse_Count(int mouse) const (0x0059FF40)
// Frame count of mouse in the table. No direct callers (inlined elsewhere).
#include "shared/mouse_class.hpp"
// @ref ?unknown_mouse_control_7e2af8@@3PAUMouseStruct@@A=007e2af8

int MouseClass::Get_Mouse_Count(int mouse) const
{
    return unknown_mouse_control_7e2af8[mouse].FrameCount;
}
