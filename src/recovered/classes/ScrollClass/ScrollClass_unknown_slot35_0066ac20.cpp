// void ScrollClass::unknown_slot35() (0x0066AC20, slot 35)
// Aborts a drag select: the display's slot 35, then releases the mouse
// capture when the main window holds it.
#include "shared/scroll.hpp"
// @ref ?unknown_slot35@DisplayClass@@UAEXXZ=0049ebf0
// @ref __imp__GetCapture@0=0079a3ec
// @ref __imp__ReleaseCapture@0=0079a3e8
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0BN@HBAO@Scroll?3?5Abort_Drag_Select?$CI?$CJ?6?$AA@=007f2c70

void ScrollClass::unknown_slot35()
{
    DisplayClass::unknown_slot35();
    unknown_4f2a = false;
    if (GetCapture() == MainWindow) {
        ReleaseCapture();
    }
    Debug_Printf("Scroll: Abort_Drag_Select()\n");
}
