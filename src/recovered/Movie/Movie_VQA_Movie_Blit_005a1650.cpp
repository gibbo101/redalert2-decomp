// void __fastcall VQA_Movie_Blit() (0x005A1650)
// Copies the current movie frame to the screen surface at its window position.
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Unknown_004E0C90@@YIX_NPAVSurface@@H@Z=004e0c90
// @ref ?MainWindow@@3PAUHWND__@@A=00b263d8
#include "shared/movie.hpp"
#include "shared/movie_globals.hpp"

void __fastcall VQA_Movie_Blit()
{
    if (CurrentVQAMovie) {
        unknown_surface_839958->Fill(0);
        Unknown_004E0C90(false, unknown_surface_839958, 0);
        if (!VQA_Unknown_0071DBA0(15)) {
            RECT client;
            GetClientRect(MainWindow, &client);
            ClientToScreen(MainWindow, (POINT *)&client);
            Rect dest(CurrentVQAMovie->Dest.X + client.left, CurrentVQAMovie->Dest.Y + client.top,
                      CurrentVQAMovie->Dest.Width, CurrentVQAMovie->Dest.Height);
            unknown_surface_839950->Copy_From(dest, *CurrentVQAMovie->FrameSurface, CurrentVQAMovie->Source, false, true);
        }
    }
}
