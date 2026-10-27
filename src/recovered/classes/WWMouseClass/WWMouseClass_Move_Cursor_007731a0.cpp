// void WWMouseClass::Move_Cursor(int x, int y, bool force) (0x007731A0)
// Moves the drawn cursor to x, y (redrawing a captured, visible cursor when
// drawing is enabled). Never called (inlined into Process_Mouse); name is a
// hypothesis. Unresolved: the flag 0x00A40D28 (also tested by DSurface::Lock).
#include "shared/wwmouse.hpp"
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Validate_Backgrounds@WWMouseClass@@QAE_NXZ=00771f50
// @ref ?Get_Cursor_Rect@WWMouseClass@@QAE?AVRect@@XZ=00772170
// @ref ?Draw_Cursor@WWMouseClass@@QAEXPAVSurface@@HH@Z=00772740
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Move_Cursor(int x, int y, bool force)
{
    Block_Mouse();
    if (x != DrawX || y != DrawY || force) {
        if (Is_Captured() && !Is_Hidden() && unknown_flag_a40d28) {
            Low_Hide_Mouse();
        }
        DrawX = x;
        DrawY = y;
        if (Is_Captured() && !Is_Hidden() && unknown_flag_a40d28) {
            Low_Show_Mouse();
        }
    }
    Unblock_Mouse();
}
