// void __fastcall Unknown_Fill_Options_Dialog_005c3550(HWND dialog, int initial) (0x005C3550)
// Fills the game options dialog from the session settings: speed, money and start unit sliders and the
// option check boxes; when first shown, the controls a World Domination Tour territory does not allow are
// disabled and the slider ranges come from the rules.
// @ref ?unknown_session_a3d2a0@@3HA=00a3d2a0
// @ref ?unknown_a3d2a4@@3HA=00a3d2a4
// @ref ?unknown_session_a3d2bc@@3HA=00a3d2bc
// @ref ?unknown_session_a3d2d0@@3HA=00a3d2d0
// @ref ?unknown_session_a3d2c2@@3EA=00a3d2c2
// @ref ?unknown_session_a3d2c3@@3EA=00a3d2c3
// @ref ?unknown_session_a3d2c4@@3HA=00a3d2c4
// @ref ?unknown_session_a3d340@@3HA=00a3d340
// @ref ?unknown_session_a3d2c8@@3HA=00a3d2c8
// @ref ?unknown_flag_a3d2c1@@3_NA=00a3d2c1
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_Territory_00769690@@YI?AV?$rc_ptr@VWDTTerritory@@@@H@Z=00769690
#include "shared/options_dialog.hpp"
#include "shared/win32_api.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/rules.hpp"
#include "shared/wdt_territory.hpp"

void __fastcall Unknown_Fill_Options_Dialog_005c3550(void *dialog_handle, int initial)
{
    HWND dialog = (HWND)dialog_handle;
    int units = unknown_session_a3d2d0;
    int money = unknown_session_a3d2bc;
    int speed = unknown_session_a3d2c8;
    if (initial) {
        rc_ptr<WDTTerritory> territory;
        if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2) {
            territory.Set(Unknown_Territory_00769690(unknown_session_a3d2a0).Pointer);
        }
        if (territory.Pointer) {
            EnableWindow(GetDlgItem(dialog, 0x544), FALSE);
            EnableWindow(GetDlgItem(dialog, 0x6d4), FALSE);
            if ((territory.Get()->unknown_3c & 0x20000) == 0) {
                EnableWindow(GetDlgItem(dialog, 0x402), FALSE);
            }
            if ((territory.Get()->unknown_3c & 0x8000) == 0) {
                EnableWindow(GetDlgItem(dialog, 0x54f), FALSE);
            }
            if ((territory.Get()->unknown_3c & 0x400) == 0) {
                EnableWindow(GetDlgItem(dialog, 0x54e), FALSE);
            }
            if ((territory.Get()->unknown_3c & 0x20) == 0) {
                EnableWindow(GetDlgItem(dialog, 1000), FALSE);
            }
            if ((territory.Get()->unknown_3c & 0x100) == 0) {
                EnableWindow(GetDlgItem(dialog, 0x54d), FALSE);
            }
        }
        SendDlgItemMessageA(dialog, 0x529, 0x406, 1, 0x60000);
        SendDlgItemMessageA(dialog, 0x402, 0x406, 1, (unsigned short)Rules->MaxMoney << 16 | (unsigned short)Rules->MinMoney);
        SendDlgItemMessageA(dialog, 0x402, 0x4ab, 0, Rules->MoneyIncrement);
        SendDlgItemMessageA(dialog, 0x54f, 0x406, 1, (unsigned short)Rules->MaxUnitCount << 16 | (unsigned short)Rules->MinUnitCount);
    }
    SendDlgItemMessageA(dialog, 0x529, 0x405, 1, 6 - speed);
    SendDlgItemMessageA(dialog, 0x402, 0x405, 1, money);
    SendDlgItemMessageA(dialog, 0x54f, 0x405, 1, units);
    int checked[2] = {0, 1};
    SendDlgItemMessageA(dialog, 0x54e, 0xf1, checked[unknown_session_a3d2c2], 0);
    SendDlgItemMessageA(dialog, 0x69a, 0xf1, checked[unknown_session_a3d2c3], 0);
    SendDlgItemMessageA(dialog, 0x69d, 0xf1, checked[(unsigned char)unknown_session_a3d2c4], 0);
    SendDlgItemMessageA(dialog, 1000, 0xf1, checked[(unsigned char)unknown_session_a3d340], 0);
    SendDlgItemMessageA(dialog, 0x54d, 0xf1, checked[unknown_flag_a3d2c1], 0);
}
