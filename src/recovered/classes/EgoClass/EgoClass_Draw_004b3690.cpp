#include "shared/ego.hpp"
#include "shared/text_print.hpp"
extern int unknown_8523e0;
extern int unknown_8523e4;
extern Surface *unknown_surface_853118;
extern bool unknown_flag_a40d28;
extern "C" unsigned int __cdecl wcslen(wchar_t const *text);
int __fastcall unknown_text_draw_005fe1b0(unsigned int color, BitFontClass *font,
    Rect const &area, wchar_t const *text, int length, int x_alignment,
    int y_alignment, Surface *surface, int unknown9);
// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?unknown_surface_853118@@3PAVSurface@@A=00853118
// @ref ?unknown_flag_a40d28@@3_NA=00a40d28
// @ref ?unknown_text_draw_005fe1b0=005fe1b0
// @ref _wcslen=00783605
void EgoClass::Draw(bool force)
{
    int y = Y;
    if (y < unknown_surface_83995c->Get_Height()) {
        y = Y;
        if (y > unknown_surface_83995c->Get_Height() - 52) goto draw;
    }
    if ((y < -16 || y > 32) && !force) return;
draw:
    Rect area((unknown_8523e0 - 520) / 2, 0, 520, unknown_8523e4);
    area.Y = y;
    int alignment = 0;
    if (TextFlags & 0x100) alignment = 1;
    else if (TextFlags & 0x200) alignment = 4;
    if (unknown_flag_a40d28)
        unknown_text_draw_005fe1b0(0x80ffff, 0, area, Text, wcslen(Text), alignment, 0, unknown_surface_853118, 0);
}
