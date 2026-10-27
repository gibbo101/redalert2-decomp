// ShapeButtonClass::ShapeButtonClass(unsigned id, void const *shape, int x, int y, int w, int h, bool flag) (0x00675060)
// Sized from the shape unless w or h is given.
#include "shared/gadget.hpp"

ShapeButtonClass::ShapeButtonClass(unsigned id, void const *shape, int x, int y, int w, int h, bool flag) :
    ToggleClass(id, x, y, 0, 0),
    unknown_34(false),
    unknown_38(0),
    unknown_40(false),
    OffsetX(0),
    OffsetY(0),
    unknown_4c(false),
    unknown_50(unknown_drawer_8323c4),
    unknown_55(flag),
    IsShapeAllocated(false)
{
    Shape = shape;
    if (shape != 0) {
        Width = ((short const *)shape)[1];
        Height = ((short const *)shape)[2];
    } else {
        Width = 0;
        Height = 0;
    }
    if (w != 0) {
        Width = w;
    }
    if (h != 0) {
        Height = h;
    }
}
