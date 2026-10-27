// ShapeButtonClass::~ShapeButtonClass() (0x006750F0)
// Frees an owned shape.
#include "shared/gadget.hpp"
// @ref ??1GadgetClass@@UAE@XZ=004cf080
// @ref ??3@YAXPAX@Z=00781d3b

ShapeButtonClass::~ShapeButtonClass()
{
    if (IsShapeAllocated && Shape != 0) {
        delete (char *)Shape;
        Shape = 0;
        IsShapeAllocated = false;
        Width = 0;
        Height = 0;
    }
}
