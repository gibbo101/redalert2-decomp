// @ref ?color_alpha@?1??Blend_Color@OwnerDraw@@YAGGGE@Z@4IA=00b2b634
// @ref ?pixel_alpha@?1??Blend_Color@OwnerDraw@@YAGGGE@Z@4IA=00b2b638
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?unknown_surface_count_a763d8@OwnerDraw@@3HA=00a763d8
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ??_7BSurface@@6B@=0079aef8
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// Draws area of the background surface from window's cached copy of what lies under it, dimmed by alpha;
// the copy is taken (from the parent's cached copy or the screen) and dimmed on first use.
void __fastcall unknown_draw_dimmed_back_5fe490(Rect const &area, HWND window, int alpha)
{
    UnknownControlRecord *record = 0;
    UnknownControlRecord *parent_record = 0;
    unknown_registry_a73640.Get(*(unsigned int *)&window, record);
    RECT client;
    GetClientRect(window, &client);
    RECT screen;
    Window_Rect_In_Main_Client(window, &screen);
    Surface *surface = record->surface_10;
    if (surface == 0) {
        surface = new BSurface(client.right + 1, client.bottom + 1, 2);
        record->surface_10 = surface;
        unknown_surface_count_a763d8++;
        Rect full(0, 0, client.right + 1, client.bottom + 1);
        HWND parent = GetParent(window);
        unknown_registry_a73640.Get(*(unsigned int *)&parent, parent_record);
        Surface *parent_surface = parent_record->surface_10;
        if (parent_surface) {
            RECT parent_screen;
            Window_Rect_In_Main_Client(parent, &parent_screen);
            Rect from;
            from.X = screen.left - parent_screen.left;
            from.Y = screen.top - parent_screen.top;
            from.Width = screen.right - screen.left + 1;
            from.Height = screen.bottom - screen.top + 1;
            surface->Copy_From(full, *parent_surface, from, false, true);
        } else {
            Surface *source = unknown_surface_839950;
            Rect from;
            from.X = screen.left;
            from.Y = screen.top;
            from.Width = screen.right - screen.left + 1;
            from.Height = screen.bottom - screen.top + 1;
            if (source) {
                surface->Copy_From(full, *source, from, false, true);
            }
        }
        unsigned short *pixels = (unsigned short *)surface->Lock();
        if (pixels) {
            for (int i = 0; i < surface->Get_Width() * surface->Get_Height(); i++) {
                pixels[i] = Blend_Color(pixels[i], 0, alpha);
            }
            surface->Unlock();
        }
    }
    Rect from;
    from.X = area.X;
    from.Y = area.Y;
    from.Width = area.Width;
    from.Height = area.Height;
    from.X -= screen.left;
    from.Y -= screen.top;
    unknown_surface_839958->Copy_From(area, *surface, from, false, true);
}

}
