// void TabClass::unknown_slot50() (0x006A0B30, slot 50)
// After the sidebar's, frees every loaded button shape.
#include "shared/tab.hpp"
// @ref ?unknown_slot50@SidebarClass@@UAEXXZ=0067bfc0
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ?ButtonShapes@TabClass@@2PAPBXA=00abd8a0
// @ref ?ButtonShapeAllocated@TabClass@@2PA_NA=00abe32c

void TabClass::unknown_slot50()
{
    SidebarClass::unknown_slot50();
    for (int index = 0; index < 25; index++) {
        Unknown_006A0540(index);
    }
}
