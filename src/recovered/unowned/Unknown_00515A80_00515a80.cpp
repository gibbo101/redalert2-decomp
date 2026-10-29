// void __fastcall Unknown_00515A80(char const *filename, bool blit) -- 0x00515A80
// Clears the hidden surface, draws the named picture on it with the palette
// 0x00838710 (0x00738190) and, when asked, blits it with the mouse.
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/palette.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90
// @ref ?unknown_palette_838710@@3VPaletteClass@@A=00838710
// @ref ?Unknown_00738190@@YIXPBDPAVSurface@@PAVPaletteClass@@@Z=00738190

extern PaletteClass unknown_palette_838710;
// Reads a picture file onto a surface with a palette (0x00738190; hypothesis).
void __fastcall Unknown_00738190(char const *filename, Surface *surface, PaletteClass *palette);

void __fastcall Unknown_00515A80(char const *filename, bool blit)
{
    unknown_surface_839954->Fill(0);
    Unknown_00738190(filename, unknown_surface_839954, &unknown_palette_838710);
    if (blit) {
        GScreenClass::Blit(true, unknown_surface_839954);
    }
}
