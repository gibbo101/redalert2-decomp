// void __fastcall Unknown_00517370(bool force) -- 0x00517370
// When the screen is marked for a redraw (0x008523DC) or force: clears the
// mark, clears the hidden surface (0x005159B0) and blits it.
#include "shared/ms_message_box.hpp"
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_redraw_8523dc@@3_NA=008523dc
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90

extern bool unknown_redraw_8523dc;

void __fastcall Unknown_00517370(bool force)
{
    if (unknown_redraw_8523dc || force) {
        unknown_redraw_8523dc = false;
        unknown_5159b0(0, true);
        GScreenClass::Blit(false, unknown_surface_839954);
    }
}
