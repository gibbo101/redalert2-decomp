// void WWMouseClass::Save_Background() (0x00772250)
// Records the cursor rectangle and copies the screen pixels under it into
// Background. Name is a hypothesis.
#include "shared/wwmouse.hpp"
// @ref _unknown_empty_rect=00b2af20
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Validate_Backgrounds@WWMouseClass@@QAE_NXZ=00771f50
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Save_Background()
{
    if (Validate_Backgrounds() && ScreenSurface != 0) {
        BackgroundRect = Get_Cursor_Rect();
        Rect rect = BackgroundRect;
        rect.X += ConfiningRect.X;
        rect.Y += ConfiningRect.Y;
        Background->Copy_From(Rect(0, 0, rect.Width, rect.Height), *ScreenSurface, rect, false, true);
    }
}
