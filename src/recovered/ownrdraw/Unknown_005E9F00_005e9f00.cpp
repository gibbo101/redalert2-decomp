// @ref ?unknown_8523e0@@3HA=008523e0
// @ref ?unknown_8523e4@@3HA=008523e4
// @ref ?unknown_dialog_a763cc@OwnerDraw@@3PAUHWND__@@A=00a763cc
// @ref ?unknown_5e9bb0@OwnerDraw@@YGHPAUHWND__@@J@Z=005e9bb0
#include "shared/win32_api.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/main_opt.hpp"
#include "shared/owner_draw_dialog_control.hpp"

// Sizes a dialog to the movie frame and moves its controls from old_size by 0x005E9BB0 (0x005E9F00).
void __fastcall Unknown_005E9F00(HWND dialog, Point2D *old_size)
{
    int width = unknown_8523e0;
    int height = unknown_8523e4;
    MoveWindow(dialog, 0, 0, width, height, 0);
    OwnerDraw::unknown_dialog_a763cc = dialog;
    LPARAM param = (LPARAM)old_size;
    EnumChildWindows(dialog, OwnerDraw::unknown_5e9bb0, param);
}
