// void WWMouseClass::Draw_Cursor(Surface *surface, int xoffset, int yoffset) (0x00772740)
// Wraps the cursor frame's pixels in a temporary 8-bit BSurface and draws it
// through unknown_convert_8323c8 at the cursor rectangle (offset), clipped to
// the confining rectangle on the screen or to the surface otherwise.
// Unresolved: the drawing function 0x0049F3A0 and its trailing arguments (0, 0, 0, 0, 1000, 0).
#include "shared/wwmouse.hpp"
// @ref ?unknown_convert_8323c8@@3PAXA=008323c8
// @ref ?unknown_blit_49f3a0@@YIXAAVSurface@@PAX0ABVRect@@ABUTPoint2D@@2HHHHHH@Z=0049f3a0
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7XSurface@@6B@=0079af8c

void WWMouseClass::Draw_Cursor(Surface *surface, int xoffset, int yoffset)
{
    if (MouseCursor == 0 || surface == 0 || unknown_convert_8323c8 == 0) {
        return;
    }
    Rect rect = BackgroundRect;
    rect.X += xoffset;
    rect.Y += yoffset;
    BSurface cursor(rect.Width, rect.Height, 1, (void *)MouseCursor->Get_Frame_Data(MouseFrame));
    if (surface == ScreenSurface) {
        unknown_blit_49f3a0(*surface, unknown_convert_8323c8, cursor, Rect(0, 0, rect.Width, rect.Height), TPoint2D(rect.X, rect.Y),
                            ConfiningRect, 0, 0, 0, 0, 1000, 0);
    } else {
        unknown_blit_49f3a0(*surface, unknown_convert_8323c8, cursor, Rect(0, 0, rect.Width, rect.Height), TPoint2D(rect.X, rect.Y),
                            surface->Get_Rect(), 0, 0, 0, 0, 1000, 0);
    }
}
