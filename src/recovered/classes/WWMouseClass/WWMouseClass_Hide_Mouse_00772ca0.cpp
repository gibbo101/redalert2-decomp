// void WWMouseClass::Hide_Mouse() (0x00772CA0, slot 3)
// Hides the cursor (nesting): at state 0 erases the captured cursor or hides
// the Windows cursor.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Hide_Mouse()
{
    Block_Mouse();
    if (MouseState == 0) {
        if (Is_Captured()) {
            Low_Hide_Mouse();
        } else {
            while (ShowCursor(0) >= 0) {
            }
        }
    }
    MouseState--;
    Unblock_Mouse();
}
