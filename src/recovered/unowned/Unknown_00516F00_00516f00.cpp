// int __fastcall Unknown_00516F00(int unknown_timeout) -- 0x00516F00
#include "shared/win32_api.hpp"
#include "shared/win32_window.hpp"
#include "shared/ms_message_box.hpp"
#include "shared/cd.hpp"
#include "shared/keyboard.hpp"
#include "shared/wstring.hpp"
#include "shared/crt_string.hpp"
#include "shared/debug_printf.hpp"
#include "shared/sound_play.hpp"
#include "shared/rules.hpp"
#include "shared/win_util.hpp"
#include "shared/random_straw.hpp"
#include "shared/gscreen.hpp"
#include "shared/dsurface.hpp"
#include "shared/unknown_globals.hpp"

// @ref ?Unknown_005171D0@@YGHPAUHWND__@@IIJ@Z=005171d0
// @ref ?unknown_create_dialog_5ff610@@YIPAUHWND__@@HP6GHPAU1@IIJ@ZH@Z=005ff610
// @ref ?unknown_dialog_5ff7c0@@YIXPAUHWND__@@@Z=005ff7c0
// @ref ?unknown_dialog_5ff6e0@@YIXPAUHWND__@@@Z=005ff6e0
// @ref ?unknown_6000d0@@YA_NXZ=006000d0
// @ref ?unknown_center_window_737080@@YIXPAUHWND__@@0@Z=00737080
// @ref ?unknown_redraw_8523dc@@3_NA=008523dc
// @ref ?unknown_5159b0@@YIXH_N@Z=005159b0
// @ref ?Blit@GScreenClass@@SIX_NPAVSurface@@PBVRect@@@Z=004e0c90
// @ref ?unknown_cheat_codes_7db500@@3PAUUnknownCheatCode@@A=007db500
// @ref ?unknown_cheat_text_a4169c@@3PADA=00a4169c
// @ref ??_C@_07CNEI@Ra2ts_l?$AA@=007db5a8
// @ref ??_C@_07IFGF@Ra2ts_s?$AA@=007db5b0
// @ref _isalnum=00782c31
// @ref _toupper=007829d3
// @ref _strstr=007836b0

extern "C" int __cdecl isalnum(int character);
// @ref _isalnum=00782c31
extern bool unknown_redraw_8523dc;
int __stdcall Unknown_005171D0(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
void __fastcall Unknown_00517370(bool force);

// A typed code (0x007DB500, four entries: PENGO, THETEAM, HIRES, TOGGLE) and the flag it toggles.
struct UnknownCheatCode {
    bool *Flag;
    char const *Code;
    char const *unknown_8;
    int unknown_c;
};
extern UnknownCheatCode unknown_cheat_codes_7db500[4];
extern char unknown_cheat_text_a4169c[32];   // 0x00A4169C the letters typed so far

// Feeds a typed letter to the code recognizer: toggles a code's flag the moment its text appears in
// what was typed; anything but a letter or digit (or '~') clears it (Tiberian Sun's
// Cheat_Key_Process; inlined into its only caller).
static bool Cheat_Key_Process(char chr)
{
    if (!isalnum(chr) || chr == '~') {
        memset(unknown_cheat_text_a4169c, 0, sizeof(unknown_cheat_text_a4169c));
        return false;
    }

    char tmp[2];
    tmp[0] = chr;
    tmp[1] = 0;
    Unknown_00496460(tmp);

    int len = strlen(unknown_cheat_text_a4169c);
    if (len >= 31) {
        len = 0;
        unknown_cheat_text_a4169c[0] = 0;
    }
    unknown_cheat_text_a4169c[len] = (char)toupper(chr);

    for (int index = 0; index < 4; index++) {
        if (strstr(unknown_cheat_text_a4169c, unknown_cheat_codes_7db500[index].Code) != 0) {
            *unknown_cheat_codes_7db500[index].Flag = !*unknown_cheat_codes_7db500[index].Flag;
            memset(unknown_cheat_text_a4169c, 0, sizeof(unknown_cheat_text_a4169c));
            return true;
        }
    }
    return false;
}

// Runs the main menu dialog 0xE2 (procedure 0x005171D0) until a button sets the choice; letters
// typed meanwhile toggle the flags of the codes they spell. 7 when the disk or dialog fails.
// Select_Game005135F0 loads ECX=3600 at005138E4 and calls00516F00 at005138E9.
// This implementation ignores the argument; its timeout meaning is a hypothesis.
int __fastcall Unknown_00516F00(int unknown_timeout)
{
    int choice = 0x12;
    CD::Set_Required_CD(-1);
    if (!CD().Force_Available(CD::RequiredCD)) {
        return 7;
    }
    HWND window = unknown_create_dialog_5ff610(0xE2, Unknown_005171D0, 0);
    if (window != 0) {
        SetWindowLongA(window, 8, (LONG)&choice);
        unknown_center_window_737080(window, MainWindow);
        unknown_dialog_5ff7c0(window);
        SetFocus(MainWindow);
        unknown_5115f0(window);
        do {
            if (unknown_6000d0()) {
                choice = 7;
            }
            Unknown_00517370(false);
            if (WWKeyboard->Check()) {
                int key = (unsigned short)WWKeyboard->Get();
                if ((key & 0x800) == 0) {
                    if (Cheat_Key_Process((char)key)) {
                        Voc_Play(Rules->OptionsChanged, 1.0f, 0x2000, 0);
                        Unknown_00517370(true);
                    }
                }
            }
        } while (choice == 0x12);
        unknown_dialog_5ff6e0(window);
        SYSTEMTIME time;
        GetSystemTime(&time);
        CryptRandom.Seed_Byte((char)time.wMilliseconds);
    } else {
        choice = 7;
    }
    SetFocus(MainWindow);
    return choice;
}
