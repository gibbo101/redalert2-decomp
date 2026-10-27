// void WWMouseClass::Low_Show_Mouse() (0x007728A0)
// Saves the background and draws the cursor on the screen under the mutex.
// Never called (inlined everywhere); name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Validate_Backgrounds@WWMouseClass@@QAE_NXZ=00771f50
// @ref ?Get_Frame_Rect@ShapeFileStruct@@QBE?AVRect@@H@Z=0045ed50
// @ref ?Draw_Cursor@WWMouseClass@@QAEXPAVSurface@@HH@Z=00772740
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Low_Show_Mouse()
{
    Block_Mouse();
    Save_Background();
    Draw_Cursor(ScreenSurface, 0, 0);
    Unblock_Mouse();
}
