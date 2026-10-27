// Point2D MouseClass::Get_Mouse_Hotspot(int mouse) const (0x0059F1D0)
// The centre or far edge of the shape file where the table asks for it,
// else 0.
#include "shared/mouse_class.hpp"
// @ref ?unknown_mouse_control_7e2af8@@3PAUMouseStruct@@A=007e2af8
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64

Point2D MouseClass::Get_Mouse_Hotspot(int mouse) const
{
    MouseShapeHeader const *shapes = MouseShapes;
    MouseStruct const &control = unknown_mouse_control_7e2af8[mouse];
    int x = 0;
    int y = 0;
    if (control.X == 12345) {
        x = shapes->Width / 2;
    }
    if (control.X == 54321) {
        x = shapes->Width;
    }
    if (control.Y == 12345) {
        y = shapes->Height / 2;
    }
    if (control.Y == 54321) {
        y = shapes->Height;
    }
    return Point2D(x, y);
}
