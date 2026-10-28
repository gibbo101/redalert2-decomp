// int __stdcall Game_Controls_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x004CFC00)
// Dialog procedure of the Game Controls dialog (the WM_COMMAND handler is a static function inlined here): the shared handler first, then
// 0x497 (initialisation: the speed, scroll rate, detail and difficulty sliders
// get their range 0-6 / 0-2 and position, the check boxes their state, the
// hotkey button is enabled when sound is available), WM_COMMAND
// (Game_Controls_Command, inlined) and WM_HSCROLL (the label next to
// the moved slider shows the text for its position).
#include "shared/game_controls_dialog.hpp"
#include "shared/options.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/sound_available.hpp"
#include "shared/unknown_globals.hpp"
#include "shared/string_table.hpp"
// @ref __imp__GetWindowLongA@8=0079a48c
// @ref ?unknown_int_a40d48@@3HA=00a40d48
// @ref __imp__GetDlgItem@8=0079a49c
// @ref __imp__SendMessageA@16=0079a4a0
// @ref __imp__ShowWindow@8=0079a498
// @ref __imp__EnableWindow@8=0079a490
// @ref ?Options@@3VOptionsClass@@A=00a40b18
// @ref ?unknown_dialog_proc_5ffb00@@YIHPAUHWND__@@IIJ@Z=005ffb00
// @ref ?unknown_check_406f30@@YAHXZ=00406f30
// @ref ?Load_String@StringTable@@SIPBGPBDPADPBDH@Z=006f9ec0
// @ref ?unknown_flag_a40d84@@3_NA=00a40d84
// @ref ?Game_Speed_Labels@@3PAPBDA=007d83c0
// @ref ?Scroll_Rate_Labels@@3PAPBDA=007d83dc
// @ref ?Detail_Level_Labels@@3PAPBDA=007d83f8
// @ref ?Difficulty_Labels@@3PAPBDA=007d8404
// @ref ??_C@_0BD@HMDA@D?3?2Ra2?2GameDlg?4CPP?$AA@=007d84d8

// WM_COMMAND of the dialog (0x004CFFB0 holds an out-of-line copy with no callers; it ends in the
// shared ret 8 that the inventory has as its own region 0x004D0020): stores the result through the
// DWL_USER pointer; 0x52C and 0x52D (notification 0, in a game) also set the radar mode 4 / 6; 0x686: 1.
static void __fastcall Game_Controls_Command(HWND window, int id, HWND control, unsigned code)
{
    int *result = (int *)GetWindowLongA(window, 8);
    switch (id) {
        case 0x52C:
            if (code == 0 && unknown_flag_a40958 == 1) {
                unknown_int_a40d48 = 4;
                *result = 1;
            }
            break;
        case 0x52D:
            if (code == 0 && unknown_flag_a40958 == 1) {
                unknown_int_a40d48 = 6;
                *result = 1;
            }
            return;
        case 0x686:
            *result = 1;
            return;
    }
}

int __stdcall Game_Controls_Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    int handled = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (handled != 0) {
        return handled;
    }
    switch (message) {
        case 0x497: {
            HWND slider = GetDlgItem(window, 0x529);
            if (unknown_game_mode_a3d298 == 0 && !unknown_flag_a40d84) {
                ShowWindow(slider, SW_HIDE);
                HWND hidden = GetDlgItem(window, 0x714);
                ShowWindow(hidden, SW_HIDE);
                hidden = GetDlgItem(window, 0x671);
                ShowWindow(hidden, SW_HIDE);
            } else if (slider) {
                SendMessageA(slider, 0x4AC, 0, 0);
                SendMessageA(slider, 0x406, 1, 0x60000);
                SendMessageA(slider, 0x405, 1, 6 - Options.GameSpeed);
            }
            if (unknown_int_a3d548) {
                HWND hidden = GetDlgItem(window, 0x529);
                ShowWindow(hidden, SW_HIDE);
                hidden = GetDlgItem(window, 0x714);
                ShowWindow(hidden, SW_HIDE);
                hidden = GetDlgItem(window, 0x671);
                ShowWindow(hidden, SW_HIDE);
            }
            slider = GetDlgItem(window, 0x52A);
            if (slider) {
                SendMessageA(slider, 0x4AC, 0, 0);
                SendMessageA(slider, 0x406, 1, 0x60000);
                SendMessageA(slider, 0x405, 1, 6 - Options.ScrollRate);
            }
            slider = GetDlgItem(window, 0x52B);
            if (slider) {
                SendMessageA(slider, 0x4AC, 0, 0);
                SendMessageA(slider, 0x406, 1, 0x20000);
                SendMessageA(slider, 0x405, 1, Options.DetailLevel);
            }
            HWND box = GetDlgItem(window, 0x601);
            if (box) {
                SendMessageA(box, 0xF1, Options.UnitActionLines != 0, 0);
            }
            box = GetDlgItem(window, 0x604);
            if (box) {
                SendMessageA(box, 0xF1, Options.ShowHidden != 0, 0);
            }
            box = GetDlgItem(window, 0x602);
            if (box) {
                SendMessageA(box, 0xF1, Options.ToolTips != 0, 0);
            }
            if (unknown_flag_a40958 == 1) {
                HWND button = GetDlgItem(window, 0x52D);
                if (button) {
                    EnableWindow(button, unknown_check_406f30());
                }
                return 0;
            }
            slider = GetDlgItem(window, 0x50F);
            if (slider) {
                SendMessageA(slider, 0x4AC, 0, 0);
                SendMessageA(slider, 0x406, 1, 0x20000);
                SendMessageA(slider, 0x405, 1, Options.Difficulty);
            }
            return 0;
        }
        case 0x111:
            Game_Controls_Command(window, wparam & 0xFFFF, (HWND)lparam, wparam >> 16);
            break;
        case 0x114:
            if ((unsigned short)wparam == 5) {
                unsigned position = wparam >> 16;
                if ((HWND)lparam == GetDlgItem(window, 0x529)) {
                    char const *label = Game_Speed_Labels[position];
                    HWND text = GetDlgItem(window, 0x671);
                    if (text) {
                        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\GameDlg.CPP", 0x1A4));
                    }
                    break;
                }
                if ((HWND)lparam == GetDlgItem(window, 0x52A)) {
                    char const *label = Scroll_Rate_Labels[position];
                    HWND text = GetDlgItem(window, 0x672);
                    if (text) {
                        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\GameDlg.CPP", 0x1A4));
                    }
                    break;
                }
                if ((HWND)lparam == GetDlgItem(window, 0x52B)) {
                    char const *label = Detail_Level_Labels[position];
                    HWND text = GetDlgItem(window, 0x673);
                    if (text) {
                        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\GameDlg.CPP", 0x1A4));
                    }
                    break;
                }
                if (!unknown_flag_a40958 && (HWND)lparam == GetDlgItem(window, 0x50F)) {
                    char const *label = Difficulty_Labels[position];
                    HWND text = GetDlgItem(window, 0x670);
                    if (text) {
                        SendMessageA(text, 0x4B2, 0, (LPARAM)StringTable::Load_String(label, 0, "D:\\Ra2\\GameDlg.CPP", 0x1A4));
                    }
                    break;
                }
            }
            break;
    }
    return 0;
}
