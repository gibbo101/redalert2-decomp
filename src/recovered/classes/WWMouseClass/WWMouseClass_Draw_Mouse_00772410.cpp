// void WWMouseClass::Draw_Mouse(Surface *surface, bool issidebar) (0x00772410, slot 15)
// Draws the captured cursor onto another surface (the sidebar one, or a
// surface offset by the sidebar width), saving what it covers first.
// Unresolved: the globals giving the offsets (0x00839638, 0x00839648,
// 0x00839948 a surface, flag 0x00A40B30).
#include "shared/wwmouse.hpp"
// @ref ?unknown_flag_a40b30@@3_NA=00a40b30
// @ref ?unknown_int_839638@@3HA=00839638
// @ref ?unknown_int_839648@@3HA=00839648
// @ref ?unknown_surface_839948@@3PAVSurface@@A=00839948
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Draw_Cursor@WWMouseClass@@QAEXPAVSurface@@HH@Z=00772740
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Draw_Mouse(Surface *surface, bool issidebar)
{
    if (Is_Hidden() || !Is_Captured() || surface == 0 || surface == ScreenSurface) {
        return;
    }
    int xoffset;
    BSurface *background;
    Rect *rect;
    if (issidebar) {
        xoffset = unknown_flag_a40b30 ? -unknown_int_839638 : 0;
        background = SidebarBackground;
        rect = &SidebarBackgroundRect;
    } else {
        xoffset = unknown_flag_a40b30 ? 0 : (-unknown_surface_839948->Get_Width() > surface->Get_Width() - unknown_int_839648
                ? -unknown_surface_839948->Get_Width()
                : surface->Get_Width() - unknown_int_839648);
        background = SurfaceBackground;
        rect = &SurfaceBackgroundRect;
    }
    if (background == 0 || Background == 0) {
        rect->Width = 0;
        return;
    }
    Block_Mouse();
    *rect = BackgroundRect;
    rect->X += xoffset;
    background->Copy_From(Rect(0, 0, rect->Width, rect->Height), *surface, *rect, false, true);
    if (issidebar && rect->X < 0 && -rect->X < Background->Get_Width()) {
        Background->Copy_From(Rect(-rect->X, 0, rect->Width, rect->Height), *surface,
                              Rect(0, rect->Y, rect->Width, rect->Height), false, true);
    } else {
        Background->Copy_From(Rect(0, 0, rect->Width, rect->Height), *surface, *rect, false, true);
    }
    Draw_Cursor(surface, xoffset, 0);
    Unblock_Mouse();
}
