// void MouseClass::Unknown_0059FEF0() (0x0059FEF0, static)
// Frees the mouse shapes when they were loaded rather than retrieved.
#include "shared/mouse_class.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?MouseShapes@MouseClass@@2PBUMouseShapeHeader@@B=00a70f64
// @ref ?MouseShapesAllocated@MouseClass@@2_NA=00a70fa4

void MouseClass::Unknown_0059FEF0()
{
    if (MouseShapesAllocated) {
        operator delete((void *)MouseShapes);
        MouseShapesAllocated = false;
    }
    MouseShapes = 0;
}
