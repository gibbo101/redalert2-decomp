// void __fastcall Unknown_00516E70() -- 0x00516E70
#include "shared/ms_message_box.hpp"
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_redraw_8523dc@@3_NA=008523dc
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90
// @ref ?Unknown_00516C40@@YGHPAUHWND__@@IIJ@Z=00516c40
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0

extern bool unknown_redraw_8523dc;
int __stdcall Unknown_00516C40(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void __fastcall Unknown_00517370(bool force);

void __fastcall Unknown_00516E70()
{
    int result = 0;
    HWND window = unknown_create_dialog_5ff610(0xD4, Unknown_00516C40, 0);
    if (window) {
        SetWindowLongA(window, 8, (LONG)&result);
        unknown_dialog_5ff7c0(window);
        while (!result) {
            if (unknown_6000d0() == true) {
                break;
            }
        Unknown_00517370(false);
        }
        unknown_dialog_5ff6e0(window);
    }
}
