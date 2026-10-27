// void MSEngine::Blit_Rect(Surface *surface, Rect const &rect) (0x005B3490)
// Copies one rectangle of surface to the screen surface (no direct callers).
#include "shared/ms_engine.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__ClientToScreen@8=0079a4ac

void MSEngine::Blit_Rect(Surface *surface, Rect const &rect)
{
    if (rect.Width > 0 && rect.Height > 0) {
        RECT client;
        GetClientRect(MainWindow, &client);
        ClientToScreen(MainWindow, (POINT *)&client);
        if (WWMouse != 0) {
            WWMouse->Draw_Mouse(surface);
        }
        Rect dest = rect;
        dest.X += client.left;
        dest.Y += client.top;
        unknown_surface_839950->Copy_From(dest, *surface, rect, false, true);
        if (WWMouse != 0) {
            WWMouse->Erase_Mouse(surface);
        }
    }
}
