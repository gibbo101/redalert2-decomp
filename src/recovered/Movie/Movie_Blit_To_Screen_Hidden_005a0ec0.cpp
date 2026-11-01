// void Movie_Blit_To_Screen_Hidden() (0x005A0EC0)
// The VQA player's frame callback for full-screen movies: unless option 15 is set, copies the frame to the
// hidden surface, draws the companion's picture centred at its bottom, then copies the hidden surface's
// source area to the movie's destination in the window's client area.
#include "shared/movie.hpp"
#include "shared/dsurface.hpp"
#include "shared/win32_api.hpp"
// @ref ?CurrentVQAMovie@@3PAVVQAMovie@@A=00a710ac
// @ref ?VQA_Unknown_0071DBA0@@YI_NH@Z=0071dba0
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
// @ref __imp__GetClientRect@8=0079a4b8
// @ref __imp__ClientToScreen@8=0079a4ac
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954

void Movie_Blit_To_Screen_Hidden()
{
    RECT rect;
    if (!VQA_Unknown_0071DBA0(15)) {
        unknown_surface_839954->Copy_From(CurrentVQAMovie->Source, *CurrentVQAMovie->FrameSurface,
                                          CurrentVQAMovie->Source, false, true);
        if (CurrentVQAMovie->Companion != 0 && CurrentVQAMovie->Companion->unknown_00 != 0) {
            Surface *picture = CurrentVQAMovie->Companion->unknown_10;
            Rect area = picture->Get_Rect();
            Rect dest;
            dest.X = (unknown_surface_839954->Get_Width() - area.Width) / 2;
            dest.Y = unknown_surface_839954->Get_Height() - area.Height;
            dest.Width = area.Width;
            dest.Height = area.Height;
            unknown_surface_839954->Copy_From(dest, *picture, area, true, true);
        }
        GetClientRect(MainWindow, &rect);
        ClientToScreen(MainWindow, (POINT *)&rect);
        Rect area;
        area.Set(rect.left + CurrentVQAMovie->Dest.X, rect.top + CurrentVQAMovie->Dest.Y,
                 CurrentVQAMovie->Dest.Width, CurrentVQAMovie->Dest.Height);
        unknown_surface_839950->Copy_From(area, *unknown_surface_839954, CurrentVQAMovie->Source, false, true);
    }
}
