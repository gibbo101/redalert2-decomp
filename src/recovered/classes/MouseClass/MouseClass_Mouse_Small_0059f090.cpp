// void MouseClass::Mouse_Small(bool wsmall) (0x0059F090, slot 21)
// Switches between the small and large forms of the current shape and sets
// the cursor again (TS Mouse_Small).
#include "shared/mouse_class.hpp"
#include "shared/mouse.hpp"
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64
// @ref ?WWMouse@@3PAVMouse@@A=00839c68

void MouseClass::Mouse_Small(bool wsmall)
{
    if (IsSmall == wsmall) {
        return;
    }
    IsSmall = wsmall;
    int start = Get_Mouse_Start_Frame(CurrentMouseShape, wsmall);
    WWMouse->Set_Cursor(Get_Mouse_Hotspot(CurrentMouseShape), (ShapeFileStruct const *)MouseShapes, start + Frame);
}
