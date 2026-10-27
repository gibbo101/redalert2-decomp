// int MouseClass::Get_Mouse_Start_Frame(int mouse, bool wsmall) const (0x0059F170)
// The small form's first frame when asked and present, else the normal one.
#include "shared/mouse_class.hpp"
// @ref ?unknown_mouse_control_7e2af8@@3PAUMouseStruct@@A=007e2af8

int MouseClass::Get_Mouse_Start_Frame(int mouse, bool wsmall) const
{
    MouseStruct const &control = unknown_mouse_control_7e2af8[mouse];
    if (wsmall && control.SmallFrame != -1) {
        return control.SmallFrame;
    }
    return control.StartFrame;
}
