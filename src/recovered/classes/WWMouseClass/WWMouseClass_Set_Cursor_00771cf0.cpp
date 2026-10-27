// void WWMouseClass::Set_Cursor(Point2D const &hotspot, ShapeFileStruct const *cursor, int frame) (0x00771CF0, slot 1)
// Selects the cursor shape, frame and hotspot; a captured, visible cursor is
// erased and redrawn around the change.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Validate_Backgrounds@WWMouseClass@@QAE_NXZ=00771f50
// @ref ?Get_Cursor_Rect@WWMouseClass@@QAE?AVRect@@XZ=00772170
// @ref ?Draw_Cursor@WWMouseClass@@QAEXPAVSurface@@HH@Z=00772740
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Set_Cursor(Point2D const &hotspot, ShapeFileStruct const *cursor, int frame)
{
    if (cursor != 0) {
        if (Is_Captured()) {
            Block_Mouse();
            if (!Is_Hidden()) {
                Low_Hide_Mouse();
            }
            MouseCursor = cursor;
            MouseFrame = frame;
            HotspotX = hotspot.X;
            HotspotY = hotspot.Y;
            if (!Is_Hidden()) {
                Low_Show_Mouse();
            }
            Unblock_Mouse();
        } else {
            MouseCursor = cursor;
            MouseFrame = frame;
            HotspotX = hotspot.X;
            HotspotY = hotspot.Y;
        }
    }
}
