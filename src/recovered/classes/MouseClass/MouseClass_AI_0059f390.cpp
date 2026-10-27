// void MouseClass::AI(int &input, Point2D const &xy) (0x0059F390, slot 10)
// Animates the current mouse shape (TS MouseClass::AI): when the shape has
// a rate and the timer ran out, steps the frame, restarts the timer and sets
// the cursor again; then the scroll layer's AI.
#include "shared/mouse_class.hpp"
#include "shared/mouse.hpp"
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Timer@MouseClass@@2V?$CDTimerClass@VSystemTimerClass@@@@A=00a70f70
// @ref ?unknown_mouse_control_7e2af8@@3PAUMouseStruct@@A=007e2af8

void MouseClass::AI(int &input, Point2D const &xy)
{
    MouseStruct const *control = &unknown_mouse_control_7e2af8[CurrentMouseShape];
    if (control->FrameRate != 0 && Timer.Value() == 0) {
        Frame++;
        Frame %= control->FrameCount;
        Timer = control->FrameRate;
        int start = Get_Mouse_Start_Frame(CurrentMouseShape, IsSmall);
        WWMouse->Set_Cursor(Get_Mouse_Hotspot(CurrentMouseShape), (ShapeFileStruct const *)MouseShapes, start + Frame);
    }
    ScrollClass::AI(input, xy);
}
