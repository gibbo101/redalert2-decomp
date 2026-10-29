// void __fastcall Unknown_00515AC0(bool blit) -- 0x00515AC0
// Fills the hidden surface with colour 0 and, when asked, blits it with the mouse.
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90

void __fastcall Unknown_00515AC0(bool blit)
{
    unknown_surface_839954->Fill(0);
    if (blit) {
        GScreenClass::Blit(true, unknown_surface_839954);
    }
}
