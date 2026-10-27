// bool MouseClass::Override_Mouse_Shape(int mouse, bool wsmall) (0x0059F250, slot 19)
// Shows another mouse shape (TS Override_Mouse_Shape): the small form only
// when the shape has one; nothing happens after the first call unless the
// shapes are loaded and the shape or form changes. Restarts the animation.
#include "shared/mouse_class.hpp"
#include "shared/mouse.hpp"
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?Timer@MouseClass@@2V?$CDTimerClass@VSystemTimerClass@@@@A=00a70f70
// @ref ?unknown_mouse_control_7e2af8@@3PAUMouseStruct@@A=007e2af8
// @ref _?startup@?1??Override_Mouse_Shape@MouseClass@@UAE_NH_N@Z@4_NA=00a70fa5

bool MouseClass::Override_Mouse_Shape(int mouse, bool wsmall)
{
    MouseStruct const *control = &unknown_mouse_control_7e2af8[mouse];
    static bool startup = false;
    if (control->SmallFrame == -1) {
        wsmall = false;
    }
    if (startup && (MouseShapes == 0 || (mouse == CurrentMouseShape && wsmall == IsSmall))) {
        return false;
    }
    startup = true;
    Timer = control->FrameRate;
    Frame = 0;
    int start = Get_Mouse_Start_Frame(mouse, wsmall);
    WWMouse->Set_Cursor(Get_Mouse_Hotspot(mouse), (ShapeFileStruct const *)MouseShapes, start);
    CurrentMouseShape = mouse;
    IsSmall = wsmall;
    return true;
}
