// bool OwnerDraw::unknown_show_tooltip_5ee110(bool): restores/draws the active tooltip.
// Native-only complete bound500 code bytes +12 padding.
// @ref ?unknown_tooltip_a737f0@OwnerDraw@@3UUnknownTooltipState@1@A=00a737f0
// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_color_a763d4@OwnerDraw@@3HA=00a763d4
// @ref ?unknown_color_a733e4@OwnerDraw@@3HA=00a733e4
// @ref ??_7BSurface@@6B@=0079aef8
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ?unknown_5fe9b0@OwnerDraw@@YIXABVRect@@AAVSurface@@HH@Z=005fe9b0
// @ref _wcslen=00783605
#include "shared/surface.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/owner_draw_dialog_control.hpp"
extern "C" unsigned int __cdecl wcslen(unsigned short const *);
namespace OwnerDraw {
void __fastcall unknown_5fe9b0(Rect const &area, Surface &surface, int a, int b);
bool __fastcall unknown_show_tooltip_5ee110(bool save_background)
{
    if (!unknown_tooltip_a737f0.shown_114) return false;
    if (save_background) {
        if (unknown_tooltip_a737f0.surface_10) delete unknown_tooltip_a737f0.surface_10;
        unknown_tooltip_a737f0.surface_10 = 0;
        Surface *background = new BSurface(unknown_tooltip_a737f0.rect_00.Width, unknown_tooltip_a737f0.rect_00.Height, 2);
        unknown_tooltip_a737f0.surface_10 = background;
        Rect destination(0, 0, unknown_tooltip_a737f0.rect_00.Width, unknown_tooltip_a737f0.rect_00.Height);
        background->Copy_From(destination, *unknown_surface_839950, unknown_tooltip_a737f0.rect_00, false, true);
    }
    unknown_tooltip_a737f0.drawn_118 = 0;
    Rect area = unknown_tooltip_a737f0.rect_00;
    int color = unknown_5fda40(unknown_color_a763d4);
    unknown_surface_839950->Lock();
    unknown_surface_839950->Fill_Rect(area, color);
    unknown_surface_839950->Unlock();
    unknown_5fe9b0(area, *unknown_surface_839950, 8, 4);
    unknown_text_draw_005fe1b0(unknown_color_a733e4, 0, area, unknown_tooltip_a737f0.text_14,
        wcslen(unknown_tooltip_a737f0.text_14), 1, 1, unknown_surface_839950, 0);
    ++area.X;
    ++area.Y;
    area.Width -= 2;
    area.Height -= 2;
    unknown_5fdb20(unknown_surface_839950, area, 1, -1);
    return true;
}
}
