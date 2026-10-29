// @ref ?unknown_surface_839950@@3PAVSurface@@A=00839950
// @ref ?unknown_surface_839958@@3PAVSurface@@A=00839958
// @ref ?Window_Rect_In_Main_Client@@YIHPAUHWND__@@PAURECT@@@Z=00735690
// @ref ?unknown_registry_a73640@OwnerDraw@@3VUnknownControlIndex@1@A=00a73640
#include "shared/unknown_globals.hpp"
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/owner_draw_dialog_control.hpp"

// WM_DRAWITEM (item is the DRAWITEMSTRUCT): while the movie surfaces exist, a type 4 control's
// registry record takes the item state and the item rectangle is repainted (0x005FE380).
void __fastcall Unknown_005FE380(long item)
{
    DRAWITEMSTRUCT *draw = (DRAWITEMSTRUCT *)item;
    if (unknown_surface_839950 && unknown_surface_839958) {
        RECT area;
        RECT client;
        Window_Rect_In_Main_Client(draw->hwndItem, &area);
        GetClientRect(draw->hwndItem, &client);
        if (GetWindowLongA(draw->hwndItem, GWL_STYLE) & 0x800000) {
            int border_x = GetSystemMetrics(5);
            int border_y = GetSystemMetrics(6);
            area.left += border_x;
            area.right -= border_x;
            area.top += border_y;
            area.bottom -= border_y;
        }
        if (draw->CtlType == 4) {
            HWND window = draw->hwndItem;
            OwnerDraw::UnknownControlRecord *record = OwnerDraw::unknown_registry_a73640.Find((unsigned int)window);
            if (record) {
                record->unknown_e8 = draw->itemState;
                InvalidateRect(window, &draw->rcItem, FALSE);
                UpdateWindow(window);
            }
        }
    }
}
