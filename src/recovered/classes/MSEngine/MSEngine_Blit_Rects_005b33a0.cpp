// void MSEngine::Blit_Rects(Surface *surface) (0x005B33A0)
// Copies every dirty rectangle of surface to the screen surface at the
// window's client origin, with the mouse drawn over it; empties the list.
#include "shared/ms_engine.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__ClientToScreen@8=0079a4ac

void MSEngine::Blit_Rects(Surface *surface)
{
    if (RectCount > 0) {
        RECT client;
        GetClientRect(MainWindow, &client);
        ClientToScreen(MainWindow, (POINT *)&client);
        if (WWMouse != 0) {
            WWMouse->Draw_Mouse(surface);
        }
        for (int index = 0; index < RectCount; index++) {
            Rect dest = Rects[index];
            dest.X += client.left;
            dest.Y += client.top;
            unknown_surface_839950->Copy_From(dest, *surface, Rects[index], false, true);
        }
        RectCount = 0;
        if (WWMouse != 0) {
            WWMouse->Erase_Mouse(surface);
        }
    }
}
