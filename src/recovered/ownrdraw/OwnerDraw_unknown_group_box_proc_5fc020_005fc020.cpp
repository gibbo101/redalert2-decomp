// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
// @ref ?Get@UnknownControlIndex@OwnerDraw@@QBE_NABIAAPAUUnknownControlRecord@2@@Z=00601710
// @ref ?unknown_window_procs_a73688@OwnerDraw@@3VUnknownWindowProcIndex@1@A=00a73688
// @ref ?unknown_color_a733e4@OwnerDraw@@3HA=00a733e4
// @ref ?unknown_color_a76158@OwnerDraw@@3HA=00a76158
// @ref ?unknown_shift_852fb8@@3HA=00852fb8
// @ref ?unknown_shift_852fbc@@3HA=00852fbc
// @ref ?unknown_shift_852fc0@@3HA=00852fc0
// @ref ?unknown_shift_852fc4@@3HA=00852fc4
// @ref ?unknown_shift_852fc8@@3HA=00852fc8
// @ref ?unknown_shift_852fcc@@3HA=00852fcc
// @ref ?Get_Text_Area@BitFontClass@@QAE_NPBGPAH1H@Z=004314b0
// @ref ?unknown_text_draw_005fe1b0@@YIHIHABVRect@@PBGHHHPAVSurface@@H@Z=005fe1b0
// @ref ??_C@_11A@?$AA?$AA@=00839d4c
// @ref _wcslen=00783605
// @ref __imp__CallWindowProcA@20=0079a4c0
// @ref __imp__ValidateRect@8=0079a3f8
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/surface.hpp"
#include "shared/text_print.hpp"
#include "shared/owner_draw_dialog_control.hpp"

namespace OwnerDraw {

// The group box window procedure: WM_PAINT prints the caption and draws the frame around it; everything
// else goes to the original procedure (0x005FC020).
LRESULT __stdcall unknown_group_box_proc_5fc020(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    switch (message) {
    default: {
        WNDPROC proc = 0;
        WNDPROC *found = unknown_window_procs_a73688.Find(window);
        if (found) {
            proc = *found;
        }
        return CallWindowProcA(proc, window, message, wparam, lparam);
    }
    case 0x14:
        return 1;
    case 0x85:
        break;
    case 0xf: {
        int gap = 0;
        UnknownControlRecord *record = Get_Record(window);
        if (!record) {
            break;
        }
        wchar_t const *text = record->text_28;
        if (!text) {
            text = L"";
        }
        RECT area;
        Window_Rect_In_Main_Client(window, &area);
        int width = area.right - area.left;
        int middle = record->font_64->Height / 2 + area.top;
        int text_width;
        int text_height;
        record->font_64->Get_Text_Area(text, &text_width, &text_height, width);
        Rect caption(area.left + 10, area.top, width, area.bottom - area.top);
        unknown_text_draw_005fe1b0(unknown_color_a733e4, 0, caption, text, wcslen(text), 0, 0, unknown_surface_839958, 0);
        int color = unknown_5fda40(unknown_color_a76158);
        unknown_surface_839958->Draw_Line(Point2D(area.left, middle), Point2D(area.left + 8, middle), color);
        if (text_width) {
            gap = 12;
        }
        unknown_surface_839958->Draw_Line(Point2D(area.left + text_width + gap, middle), Point2D(area.right, middle), color);
        unknown_surface_839958->Draw_Line(Point2D(area.left, middle), Point2D(area.left, area.bottom), color);
        unknown_surface_839958->Draw_Line(Point2D(area.left, area.bottom), Point2D(area.right, area.bottom), color);
        unknown_surface_839958->Draw_Line(Point2D(area.right, middle), Point2D(area.right, area.bottom), color);
        ValidateRect(window, 0);
        break;
    }
    }
    return 0;
}

}
