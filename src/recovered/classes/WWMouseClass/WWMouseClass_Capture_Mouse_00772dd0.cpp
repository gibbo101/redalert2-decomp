// void WWMouseClass::Capture_Mouse() (0x00772DD0, slot 6)
// Switches to the software cursor: draws it if visible and hides the Windows
// cursor (name from the debug string).
#include "shared/wwmouse.hpp"
// @ref ??_C@_0BB@KEPO@Capture_Mouse?$CI?$CJ?6?$AA@=008013c8
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Validate_Backgrounds@WWMouseClass@@QAE_NXZ=00771f50
// @ref ?Get_Frame_Rect@ShapeFileStruct@@QBE?AVRect@@H@Z=0045ed50
// @ref ??0Rect@@QAE@HHHH@Z=0042bcd0
// @ref ?Block_Mouse@@YAXXZ=00773630
// @ref ?Draw_Cursor@WWMouseClass@@QAEXPAVSurface@@HH@Z=00772740
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Capture_Mouse()
{
    if (this != 0 && !Is_Captured()) {
        Debug_Printf("Capture_Mouse()\n");
        Block_Mouse();
        IsCaptured = true;
        if (!Is_Hidden()) {
            Low_Show_Mouse();
        }
        ShowCursor(0);
        Unblock_Mouse();
    }
}
