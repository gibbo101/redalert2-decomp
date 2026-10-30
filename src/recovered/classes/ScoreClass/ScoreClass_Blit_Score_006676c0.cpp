// void ScoreClass::Blit_Score() (0x006676C0)
// Copies the 640x400 score area of the score surface to the screen at the
// window's client origin (as MSEngine::Blit_Rect 0x005B3490).
#include "shared/score.hpp"
#include "shared/ms_engine.hpp"
#include "shared/mouse.hpp"
#include "shared/win32_window.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__ClientToScreen@8=0079a4ac

void ScoreClass::Blit_Score()
{
    RECT client;
    GetClientRect(MainWindow, &client);
    ClientToScreen(MainWindow, (POINT *)&client);
    Rect dest(XOffset + client.left, YOffset + client.top, 640, 400);
    Rect source(XOffset, YOffset, 640, 400);
    if (WWMouse != 0) {
        WWMouse->Draw_Mouse(unknown_surface_839954);
    }
    unknown_surface_839950->Copy_From(dest, *unknown_surface_839954, source, false, true);
    if (WWMouse != 0) {
        WWMouse->Erase_Mouse(unknown_surface_839954);
    }
}
