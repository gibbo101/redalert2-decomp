// void MouseClass::One_Time() (0x0059F4F0, slot 5)
// After the scroll layer's, loads the mouse shapes "MOUSE.SHP".
#include "shared/mouse_class.hpp"
// @ref ?One_Time@TabClass@@UAEXXZ=006a0b20
// @ref ?Unknown_Load_Shape_00495270@@YIPBXPBDAA_N@Z=00495270
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64
// @ref ?MouseShapesAllocated@MouseClass@@2_NA=00a70fa4

void MouseClass::One_Time()
{
    ScrollClass::One_Time();
    MouseShapes = (MouseShapeHeader const *)Unknown_Load_Shape_00495270("MOUSE.SHP", MouseShapesAllocated);
}
// @ref ??_C@_09JKEA@MOUSE?4SHP?$AA@=007db964
