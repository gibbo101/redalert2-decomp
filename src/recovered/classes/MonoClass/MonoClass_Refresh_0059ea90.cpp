// void MonoClass::Refresh(int x, int y, int width, int height) (0x0059EA90)
// Redraws a block of cells on the game window if this is the window on display.
#include "shared/win32_gdi.hpp"
#include "shared/mono_class.hpp"
// @ref ?unknown_mono_enabled_a70f0a@@3_NA=00a70f0a
// @ref ?unknown_mono_viewed_a70f0c@@3PAVMonoClass@@A=00a70f0c
// @ref ?unknown_mono_window_a70f10@@3PAUHWND__@@A=00a70f10
// @ref ?unknown_mono_font_a70f14@@3PAXA=00a70f14
// @ref ?unknown_mono_text_color_a70de8@@3KA=00a70de8
// @ref ?unknown_mono_back_color_a70e00@@3KA=00a70e00
// @ref ?Draw_Character@MonoClass@@QAEXPAUHDC__@@HH@Z=0059e9d0
// @ref __imp__GetDC@4=0079a458
// @ref __imp__ReleaseDC@8=0079a478
// @ref __imp__SetBkMode@8=0079a07c
// @ref __imp__SetBkColor@8=0079a06c
// @ref __imp__SetTextColor@8=0079a068
// @ref __imp__SelectObject@8=0079a064

void MonoClass::Refresh(int x, int y, int width, int height)
{
    if (unknown_mono_enabled_a70f0a && this == unknown_mono_viewed_a70f0c) {
        HDC dc = GetDC(unknown_mono_window_a70f10);
        SetBkMode(dc, 2);
        SetBkColor(dc, unknown_mono_back_color_a70e00);
        SetTextColor(dc, unknown_mono_text_color_a70de8);
        if (dc != 0) {
            HGDIOBJ old_font = SelectObject(dc, unknown_mono_font_a70f14);
            for (int row = y; row < y + height; row++) {
                for (int column = x; column < x + width; column++) {
                    Draw_Character(dc, column, row);
                }
            }
            SelectObject(dc, old_font);
            ReleaseDC(unknown_mono_window_a70f10, dc);
        }
    }
}
