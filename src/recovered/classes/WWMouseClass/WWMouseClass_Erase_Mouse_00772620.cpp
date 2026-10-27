// void WWMouseClass::Erase_Mouse(Surface *surface, bool issidebar) (0x00772620, slot 16)
// Restores the pixels Draw_Mouse saved on that surface.
#include "shared/wwmouse.hpp"
// @ref ?MouseMutex@@3PAXA=00b2af60
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??_C@_0EA@PAMP@Warning?3?5Probable?5deadlock?5occur@=00801318
// @ref ??_C@_0BC@JOPK@D?3?2Ra2?2wwmous?4cpp?$AA@=00801358

void WWMouseClass::Erase_Mouse(Surface *surface, bool issidebar)
{
    if (Is_Hidden() || !Is_Captured() || surface == 0 || surface == ScreenSurface || SurfaceBackground == 0
        || SidebarBackground == 0) {
        return;
    }
    BSurface *background;
    Rect rect;
    if (issidebar) {
        background = SidebarBackground;
        rect = SidebarBackgroundRect;
    } else {
        background = SurfaceBackground;
        rect = SurfaceBackgroundRect;
    }
    if (background != 0) {
        Block_Mouse();
        surface->Copy_From(rect, *background, Rect(0, 0, rect.Width, rect.Height), false, true);
        Unblock_Mouse();
    }
}
