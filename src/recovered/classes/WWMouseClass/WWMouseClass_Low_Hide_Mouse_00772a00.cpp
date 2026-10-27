// void WWMouseClass::Low_Hide_Mouse() (0x00772A00)
// Erases the cursor from the screen under the mutex. Never called (inlined
// everywhere); name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Low_Hide_Mouse()
{
    Block_Mouse();
    Restore_Background();
    Unblock_Mouse();
}
