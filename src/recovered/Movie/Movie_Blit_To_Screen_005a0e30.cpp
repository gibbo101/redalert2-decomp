// void Movie_Blit_To_Screen() (0x005A0E30)
// The VQA player's frame callback for windowed movies (TibSun Movie_Blit_To_Screen): unless option 15 is
// set, copies the frame's source area to the movie's destination in the window's client area.
#include "shared/movie.hpp"
#include "shared/win32_api.hpp"
// @ref ?CurrentVQAMovie@@3PAVVQAMovie@@A=00a710ac
// @ref ?VQA_Unknown_0071DBA0@@YI_NH@Z=0071dba0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__ClientToScreen@8=0079a4ac
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950

void Movie_Blit_To_Screen()
{
    RECT rect;
    if (!VQA_Unknown_0071DBA0(15)) {
        GetClientRect(MainWindow, &rect);
        ClientToScreen(MainWindow, (POINT *)&rect);
        Rect area;
        area.Set(rect.left + CurrentVQAMovie->Dest.X, rect.top + CurrentVQAMovie->Dest.Y,
                 CurrentVQAMovie->Dest.Width, CurrentVQAMovie->Dest.Height);
        unknown_surface_839950->Copy_From(area, *CurrentVQAMovie->FrameSurface, CurrentVQAMovie->Source, false, true);
    }
}
