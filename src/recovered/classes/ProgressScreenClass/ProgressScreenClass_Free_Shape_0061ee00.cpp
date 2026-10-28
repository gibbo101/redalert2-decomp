// void ProgressScreenClass::Free_Shape() (0x0061EE00): deletes the shape when
// it was allocated.
#include "shared/progress_screen.hpp"

void ProgressScreenClass::Free_Shape()
{
    if (ShapeAllocated) {
        delete (void *)Shape;
        ShapeAllocated = false;
    }
    Shape = 0;
}
