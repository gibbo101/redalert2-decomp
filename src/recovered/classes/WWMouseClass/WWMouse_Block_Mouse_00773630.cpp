// void Block_Mouse() (0x00773630)
// Takes the mouse mutex, warning after 10 seconds (the warning names line 1277
// of the original file, hence the literal). VC6 expands it into the earlier
// callers; Show/Capture_Mouse call this copy.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void Block_Mouse()
{
    if (WaitForSingleObject(MouseMutex, 10000) == WAIT_TIMEOUT) {
        Debug_Printf("Warning: Probable deadlock occurred on MouseMutex. %s, line %d\n", "D:\\Ra2\\wwmous.cpp", 1277);
    }
}
