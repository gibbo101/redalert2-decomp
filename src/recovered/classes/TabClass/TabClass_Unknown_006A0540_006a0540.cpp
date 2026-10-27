// void __fastcall TabClass::Unknown_006A0540(int index) (0x006A0540)
// Frees button shape index when it was loaded rather than retrieved.
#include "shared/tab.hpp"
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?ButtonShapes@TabClass@@2PAPBXA=00abd8a0
// @ref ?ButtonShapeAllocated@TabClass@@2PA_NA=00abe32c

void __fastcall TabClass::Unknown_006A0540(int index)
{
    if (ButtonShapeAllocated[index]) {
        operator delete((void *)ButtonShapes[index]);
        ButtonShapeAllocated[index] = false;
    }
    ButtonShapes[index] = 0;
}
