// bool OptionsClass::Unknown_005DA360() (0x005DA360)
// Runs dialog 0xA3 (procedure 0x005D97A0) until it sets its result or the dialog handler ends the wait;
// outside a game the title screen keeps being serviced. Does not use its receiver; always true.
#include "shared/options.hpp"
#include "shared/dialog_create.hpp"
#include "shared/unknown_globals.hpp"
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref __imp__SetWindowLongA@12=0079a488
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_517370@@YIX_N@Z=00517370
// @ref ?Unknown_Options_Dialog_Proc_005d97a0@@YGHPAUHWND__@@IIJ@Z=005d97a0

void __fastcall unknown_dialog_5ff7c0(HWND window);      // 0x005FF7C0 (shared/ms_message_box.hpp)
void __fastcall unknown_dialog_5ff6e0(HWND window);      // 0x005FF6E0
void __fastcall unknown_517370(bool unknown1);           // 0x00517370
int __stdcall Unknown_Options_Dialog_Proc_005d97a0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

bool OptionsClass::Unknown_005DA360()
{
    int rc = -1;
    HWND dialog = unknown_create_dialog_5ff610(0xA3, Unknown_Options_Dialog_Proc_005d97a0, 0);
    if (dialog) {
        SetWindowLongA(dialog, 8, (LONG)&rc);
        unknown_dialog_5ff7c0(dialog);
        while (rc < 0) {
            if (unknown_6000d0() == true) {
                rc = 2;
            }
            if (!unknown_flag_a40958) {
                unknown_517370(false);
            }
        }
        unknown_dialog_5ff6e0(dialog);
    }
    return true;
}
