// void WWMouseClass::Release_Mouse() (0x00772FA0, slot 5)
// Returns to the Windows cursor: erases the software cursor and shows the
// Windows one if visible (name from the debug string).
#include "shared/wwmouse.hpp"
// @ref ??_C@_0BB@NBHB@Release_Mouse?$CI?$CJ?6?$AA@=008013dc
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Release_Mouse()
{
    if (this != 0 && Is_Captured()) {
        Debug_Printf("Release_Mouse()\n");
        Block_Mouse();
        IsCaptured = false;
        if (!Is_Hidden()) {
            Low_Hide_Mouse();
            while (ShowCursor(1) < 0) {
            }
        }
        Unblock_Mouse();
    }
}
