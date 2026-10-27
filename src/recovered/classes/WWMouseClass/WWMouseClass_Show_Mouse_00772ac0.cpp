// void WWMouseClass::Show_Mouse() (0x00772AC0, slot 4)
// Undoes one Hide_Mouse; at state 0 draws the captured cursor or shows the
// Windows cursor.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Validate_Backgrounds@WWMouseClass@@QAE_NXZ=00771f50
// @ref ?Get_Frame_Rect@ShapeFileStruct@@QBE?AVRect@@H@Z=0045ed50
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ?Block_Mouse@@YAXXZ=00773630
// @ref ?Draw_Cursor@WWMouseClass@@QAEXPAVSurface@@HH@Z=00772740
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Show_Mouse()
{
    if (MouseState != 0) {
        Block_Mouse();
        MouseState++;
        if (MouseState == 0) {
            if (Is_Captured()) {
                Low_Show_Mouse();
            } else {
                while (ShowCursor(1) < 0) {
                }
            }
        }
        if (MouseState > 0) {
            MouseState = 0;
        }
        Unblock_Mouse();
    }
}
