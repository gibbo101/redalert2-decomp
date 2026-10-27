// Rect WWMouseClass::Get_Cursor_Rect() (0x00772170)
// Rectangle of the current cursor frame placed at the drawing position, relative
// to ConfiningRect (empty without a cursor). Name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref _unknown_empty_rect=00b2af20
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

Rect WWMouseClass::Get_Cursor_Rect()
{
    Rect rect(0, 0, 0, 0);
    if (MouseCursor != 0) {
        Block_Mouse();
        rect = MouseCursor->Get_Frame_Rect(MouseFrame);
        rect.X += DrawX - HotspotX;
        rect.Y += DrawY - HotspotY;
        Unblock_Mouse();
    }
    return rect;
}
