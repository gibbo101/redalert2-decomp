// void ShapeButtonClass::Set_Shape(void const *shape, int w, int h) (0x00675130, slot 34)
// Replaces the shape (freeing an owned one) and takes its size from the shape
// header (+2 width, +4 height) unless w or h is given.
#include "shared/gadget.hpp"

void ShapeButtonClass::Set_Shape(void const *shape, int w, int h)
{
    if (IsShapeAllocated && Shape != 0) {
        delete (char *)Shape;
        Shape = 0;
        IsShapeAllocated = false;
        Width = 0;
        Height = 0;
    }
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
