// int __stdcall Game_Options_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x004DDF90)
// Dialog 0xB6 (the leave-game choice): the leave button (0x6C9) returns Leave_Result (2, or 3 when the
// player may stay to observe), the second button (0x712) restarts (5) in the campaign, observes (4) in
// game modes 3 and 4 while at least two human houses are still in the game, and is hidden otherwise.
#include "shared/game_options_dialog.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/house.hpp"
#include "shared/string_table.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_5e2040@@YIXPAUHWND__@@H@Z=005e2040
// @ref ?Load_String@StringTable@@SIPBGPBDPADPBDH@Z=006f9ec0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Houses@@3V?$DynamicVectorClass@PAVHouseClass@@@@A=00a32298
// @ref _Leave_Result=00a40e1c
// @ref _Other_Result=00a40e20
// @ref ??_C@_0BE@CLPH@D?3?2Ra2?2GOptions?4CPP?$AA@=007d9c9c
// @ref ??_C@_09GNCJ@GUI?3Leave?$AA@=007d9cc8
// @ref ??_C@_0M@BIAC@GUI?3Restart?$AA@=007d9cbc
// @ref ??_C@_0M@HDJ@GUI?3Observe?$AA@=007d9cb0

void __fastcall unknown_5e2040(HWND window, int value);   // 0x005E2040 (an owner-draw button's value)

static int Leave_Result;    // 0x00A40E1C
static int Other_Result;    // 0x00A40E20

int __stdcall Game_Options_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x497: {
            HWND leave = GetDlgItem(window, 0x6C9);
            SendMessageA(leave, 0x4B2, 0, (LPARAM)StringTable::Load_String("GUI:Leave", 0, "D:\\Ra2\\GOptions.CPP", 0x21F));
            Leave_Result = 2;
            HWND other = GetDlgItem(window, 0x712);
            Other_Result = 0;
            if (unknown_game_mode_a3d298 == 0) {
                SendMessageA(other, 0x4B2, 0, (LPARAM)StringTable::Load_String("GUI:Restart", 0, "D:\\Ra2\\GOptions.CPP", 0x22A));
                Other_Result = 5;
            } else if (unknown_game_mode_a3d298 == 5) {
                ShowWindow(other, SW_HIDE);
            } else if (unknown_game_mode_a3d298 == 3 || unknown_game_mode_a3d298 == 4) {
                int humans = 0;
                for (int index = 0; index < Houses.Count(); index++) {
                    HouseClass *house = Houses[index];
                    if (house->unknown_134 && !house->unknown_13d) {
                        humans++;
                    }
                }
                if (humans >= 2 && !unknown_player_a35db4->unknown_13d) {
                    Leave_Result = 3;
                    SendMessageA(other, 0x4B2, 0, (LPARAM)StringTable::Load_String("GUI:Observe", 0, "D:\\Ra2\\GOptions.CPP", 0x246));
                    Other_Result = 4;
                } else {
                    ShowWindow(other, SW_HIDE);
                }
            }
            unknown_5e2040(leave, Leave_Result);
            unknown_5e2040(other, Other_Result);
            break;
        }
        case 0x111: {
            int *result = (int *)GetWindowLongA(window, 8);
            unsigned short code = wparam >> 16;
            int id = wparam & 0xFFFF;
            if (code == 0) {
                switch (id) {
                    case 1:
                    case 0x686:
                        *result = 1;
                        return 0;
                    case 0x6C9:
                        *result = Leave_Result;
                        return 0;
                    case 0x712:
                        *result = Other_Result;
                        break;
                }
            }
            break;
        }
    }
    return 0;
}
