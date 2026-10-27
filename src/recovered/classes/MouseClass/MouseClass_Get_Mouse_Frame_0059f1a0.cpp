// int MouseClass::Get_Mouse_Frame(int mouse, bool wsmall) const (0x0059F1A0)
// The current animation frame of mouse.
#include "shared/mouse_class.hpp"
// @ref ?unknown_mouse_control_7e2af8@@3PAUMouseStruct@@A=007e2af8

int MouseClass::Get_Mouse_Frame(int mouse, bool wsmall) const
{
    return Frame + Get_Mouse_Start_Frame(mouse, wsmall);
}
