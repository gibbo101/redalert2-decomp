// void __fastcall unknown_5159b0(int unknown1, bool unknown2) -- 0x005159B0
// Body 0x005159B0-0x00515A79 (202 bytes, nop padding to 0x00515A80). unknown1 is really the surface to draw
// on (0: unknown_surface_839954) and unknown2 whether to blit it afterwards; the declaration in
// shared/unknown_globals.hpp keeps its int parameter until a rename spec changes the signature.
#include "shared/surface.hpp"
#include "shared/dsurface.hpp"
#include "shared/rect.hpp"
#include "shared/movie_globals.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?Unknown_006F3A20@@YIXPAVSurface@@ABVRect@@_N@Z=006f3a20

void __fastcall Unknown_006F3A20(Surface *surface, Rect const &window, bool arg3);   // 0x006F3A20

// Clears the surface and redraws the menu background into it through a 16-bit work surface of the same
// size (0x006F3A20 draws it), then blits it when asked (name hypothesis: the main menu background).
void __fastcall unknown_5159b0(int unknown1, bool unknown2)
{
    Surface *surface = (Surface *)unknown1;
    if (surface == 0) {
        surface = unknown_surface_839954;
    }
    surface->Fill(0);
    int width = surface->Get_Width();
    int height = surface->Get_Height();
    Rect rect(0, 0, width, height);
    BSurface *work = new BSurface(width, height, 2);
    Unknown_006F3A20(work, rect, false);
    surface->Copy_From(*work, false, true);
    delete work;
    if (unknown2) {
        Unknown_004E0C90(false, surface, 0);
    }
}
