// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?unknown_window_procs_a73688@OwnerDraw@@3VUnknownWindowProcIndex@1@A=00a73688
// @ref ?unknown_surface_count_a763d8@OwnerDraw@@3HA=00a763d8
// @ref ?unknown_color_a733e4@OwnerDraw@@3HA=00a733e4
// @ref ?unknown_hotkey_text_5fc600@OwnerDraw@@YIXGPAG@Z=005fc600
// @ref ?unknown_5fdb20@OwnerDraw@@YIXPAVSurface@@ABVRect@@HH@Z=005fdb20
// @ref ?unknown_draw_text_5fdf40@OwnerDraw@@YIHPAVSurface@@PBGPAURECT@@PAVBitFontClass@@KH@Z=005fdf40
// @ref ??2@YAPAXI@Z=00782017
// @ref ??0Buffer@@QAE@PAXJ@Z=004382c0
// @ref ??_7XSurface@@6B@=0079af8c
// @ref ??_7BSurface@@6B@=0079aef8
// @ref _wcslen=00783605
// @ref __imp__CallWindowProcA@20=0079a4c0
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ValidateRect@8=0079a3f8
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// The msctls_hotkey32 window procedure: WM_PAINT draws the frame and the hot key's text over the saved
// background; everything else goes to the original procedure (0x005FC330).
LRESULT __stdcall unknown_hotkey_proc_5fc330(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    case 0xf: {
        RECT area;
        Window_Rect_In_Main_Client(window, &area);
        Rect screen(area.left, area.top, area.right - area.left + 1, area.bottom - area.top + 1);
        Rect local(0, 0, screen.Width, screen.Height);
        UnknownControlRecord *record = 0;
        unknown_registry_a73640.Get((unsigned int)window, record);
        if (!record) {
            return 0;
        }
        if (!record->surface_10) {
            Surface *surface = new BSurface(screen.Width, screen.Height, 2);
            record->surface_10 = surface;
            unknown_surface_count_a763d8++;
            surface->Copy_From(local, *unknown_surface_839958, screen, false, true);
        }
        wchar_t text[64];
        unsigned short hotkey = (unsigned short)SendMessageA(window, 0x402, 0, 0);
        unknown_hotkey_text_5fc600(hotkey, text);
        if (record->surface_10) {
            unknown_surface_839958->Copy_From(screen, *record->surface_10, local, false, true);
        }
        unknown_5fdb20(unknown_surface_839958, screen, 1, -1);
        if (wcslen(text) > 0) {
            area.left += 4;
            area.top += 4;
            area.right -= 4;
            area.bottom -= 4;
            unknown_draw_text_5fdf40(unknown_surface_839958, text, &area, record->font_64, unknown_color_a733e4, 0x24);
        }
        ValidateRect(window, 0);
        return 0;
    }
    case 0x14:
        return 1;
    case 0x85:
        return 0;
    }
    WNDPROC proc = 0;
    WNDPROC *found = unknown_window_procs_a73688.Find(window);
    if (found) {
        proc = *found;
    }
    return CallWindowProcA(proc, window, message, wparam, lparam);
}

}
