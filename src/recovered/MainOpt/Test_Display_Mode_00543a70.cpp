// bool __fastcall Test_Display_Mode(int width, int height) (0x00543A70)
// Switches to the display mode, shows the confirmation dialog 0xD9 for 600 ticks (restarted at 300
// after the dialog is told to cancel) and keeps the mode when it is answered with 1; otherwise
// switches back to the Options resolution.
#include "shared/main_opt.hpp"
#include "shared/movie_globals.hpp"
#include "shared/dsurface.hpp"
#include "shared/debug_printf.hpp"
#include "shared/cd_timer.hpp"
#include "shared/system_timer.hpp"
// @ref __imp__SetWindowLongA@12=0079a488
// @ref __imp__PostMessageA@16=0079a470
// @ref ?WWMouse@@3PAVMouse@@A=00839c68
// @ref ?unknown_surface_839954@@3PAVDSurface@@A=00839954
// @ref ?unknown_surface_83995c@@3PAVSurface@@A=0083995c
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?Debug_Printf@@YAXPBDZZ=004068f0
// @ref ??BSystemTimerClass@@QBEJXZ=0069a430
// @ref ?Unknown_004E0C90@@YIX_NPAVSurface@@H@Z=004e0c90
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?Set_Display_Mode@@YI_NHH@Z=005434e0
// @ref ?Confirm_Mode_Proc@@YGHPAUHWND__@@IIJ@Z=00543c40
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ??_C@_0BO@FBHC@Testing?5display?5mode?5?$EA?5?$CFdx?$CFd?6?$AA@=007e008c
// @ref ??_C@_0BO@IHHO@Keeping?5display?5mode?5?$EA?5?$CFdx?$CFd?6?$AA@=007e004c
// @ref ??_C@_0CA@MBMA@Resetting?5display?5mode?5?$EA?5?$CFdx?$CFd?6?$AA@=007e006c

bool __fastcall Test_Display_Mode(int width, int height)
{
    int result = -1;
    Debug_Printf("Testing display mode @ %dx%d\n", width, height);
    WWMouse->Hide_Mouse();
    unknown_surface_839954->Fill(0);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    if (!Set_Display_Mode(width, height)) {
        return false;
    }
    unknown_surface_839954->Fill(0);
    Unknown_004E0C90(true, unknown_surface_839954, 0);
    WWMouse->Show_Mouse();
    unknown_5159b0(0, true);
    HWND dialog = unknown_create_dialog_5ff610(0xD9, Confirm_Mode_Proc, 0);
    if (dialog) {
        SetWindowLongA(dialog, 8, (LONG)&result);
        unknown_dialog_5ff7c0(dialog);
        CDTimerClass<SystemTimerClass> timer(600);
        while (result < 0) {
            if (unknown_6000d0() == true) {
                break;
            }
            unknown_517370(false);
            if (timer <= 0) {
                PostMessageA(dialog, 0x111, 0x6CA, 0);
                timer = 300;
            }
        }
        unknown_dialog_5ff6e0(dialog);
        if (result != 1) {
            Debug_Printf("Resetting display mode @ %dx%d\n", Options.ScreenWidth, Options.ScreenHeight);
            Set_Display_Mode(Options.ScreenWidth, Options.ScreenHeight);
            unknown_surface_83995c = unknown_surface_839954;
            return false;
        }
    }
    Debug_Printf("Keeping display mode @ %dx%d\n", width, height);
    unknown_surface_83995c = unknown_surface_839954;
    return true;
}
