// Starts an owner-drawn tooltip after closing the previous one.
// @ref ?unknown_tooltip_a737f0@OwnerDraw@@3UUnknownTooltipState@1@A=00a737f0
// @ref ?unknown_tooltip_time_a763fc@OwnerDraw@@3JA=00a763fc
// @ref _unknown_tooltip_label_7eadc0=007eadc0
// @ref _unknown_ownrdraw_file_7e8df8=007e8df8
// @ref ?unknown_show_tooltip_5ee110@OwnerDraw@@YI_N_N@Z=005ee110
// @ref _time=0078387f
// @ref _swprintf=00783764
// @ref _wcscpy=00783689
#include "shared/owner_draw_dialog_control.hpp"
extern "C" long __cdecl time(long *);
extern "C" int __cdecl swprintf(unsigned short *, unsigned short const *, ...);
extern "C" unsigned short *__cdecl wcscpy(unsigned short *, unsigned short const *);
extern "C" char const unknown_tooltip_label_7eadc0[];
extern "C" char const unknown_ownrdraw_file_7e8df8[];
namespace OwnerDraw {
extern long unknown_tooltip_time_a763fc;
bool __fastcall unknown_show_tooltip_5ee110(bool save_background);
bool __fastcall unknown_start_tooltip_5edfd0(Rect const &area, unsigned short const *text, HWND window)
{
    unknown_5ee3b0();
    unknown_tooltip_time_a763fc = time(0);
    swprintf(unknown_tooltip_a737f0.text_14, StringTable::Load_String(unknown_tooltip_label_7eadc0, 0, unknown_ownrdraw_file_7e8df8, 0x1a88));
    if (text) wcscpy(unknown_tooltip_a737f0.text_14, text);
    unknown_tooltip_a737f0.rect_00 = area;
    unknown_tooltip_a737f0.shown_114 = 1;
    unknown_tooltip_a737f0.unknown_11c = (int)window;
    return unknown_show_tooltip_5ee110(true);
}
}
