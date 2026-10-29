// void __fastcall Options_Menu_Init(HWND window) (0x004DDE00): sets up the in-game options menu (dialog
// 0xB5/0xBBA/0xFF of Unknown_004DD7D0): in single-player games the load (0x51E) and delete (0x520)
// buttons are enabled while saved games exist; in game mode 4 (without unknown_int_a3d548) the latency
// (0x3EF, 0-2) and game speed (0x529, 0-6) sliders get their range and position.
#include "shared/game_options_dialog.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/map_seed.hpp"
#include "shared/options.hpp"
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__EnableWindow@8=0079a490
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_int_a3d548@@3HA=00a3d548
// @ref ?unknown_a3fba4@@3HA=00a3fba4
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ??0LoadOptionsClass@@QAE@XZ=0053b0e0
// @ref ??1LoadOptionsClass@@UAE@XZ=0053b130
// @ref ?Has_Saved_Games_0053c5c0@LoadOptionsClass@@QAE_NXZ=0053c5c0


void __fastcall Options_Menu_Init(HWND window)
{
    if (unknown_game_mode_a3d298 == 0 || unknown_game_mode_a3d298 == 5) {
        bool saved = LoadOptionsClass().Has_Saved_Games_0053c5c0();
        HWND button = GetDlgItem(window, 0x51E);
        if (button) {
            EnableWindow(button, saved);
        }
        button = GetDlgItem(window, 0x520);
        if (button) {
            EnableWindow(button, saved);
        }
    } else if (unknown_game_mode_a3d298 == 4 && !unknown_int_a3d548) {
        HWND slider = GetDlgItem(window, 0x3EF);
        if (slider) {
            int latency = 3 - unknown_a3fba4;
            SendMessageA(slider, 0x406, 1, 0x30000);
            SendMessageA(slider, 0x405, 1, latency);
        }
        slider = GetDlgItem(window, 0x529);
        if (slider) {
            SendMessageA(slider, 0x406, 1, 0x60000);
            SendMessageA(slider, 0x405, 1, 6 - Options.GameSpeed);
        }
    }
}
