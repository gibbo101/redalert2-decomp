// int Join_WOL_Lobby(HWND window, bool first_time) (0x00743720): the online lobby screen (TibSun Join_WOL_Lobby).
#include "shared/wol_sink.hpp"
#include "shared/lobby.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/crt_time.hpp"
#include "shared/crt_tokens.hpp"
#include "shared/session_state.hpp"
#include "shared/wol_main.hpp"
#include "shared/debug_printf.hpp"
extern "C" __declspec(dllimport) DWORD __stdcall WaitForMultipleObjects(DWORD, HANDLE *, BOOL, DWORD);
extern HANDLE wol_wait_events_b264f8[18];
extern bool connection_wait_callback_0073c120();
extern char wol_channel_list_label_007fd754[], wol_joining_label_7fe688[], wol_source_file_007fd62c[];
extern char wol_login_complete_label_7fe694[], wol_motd_separator_7f3830[];
extern unsigned short wol_wide_newline_7e58ec[];
extern bool unknown_wdt_sounds_initialized_b2ac28;
extern int wol_lan_leave_b2abf0;
extern int unknown_7fd300;
extern bool unknown_7fd354;
extern int unknown_time_b2abd0, unknown_time_b2abd4;
extern HWND game_window_00b263d8;
void __fastcall Open_Wait_Window_0074d4d0(unsigned int, WideString const &, bool);
void __fastcall unknown_5159b0(int, bool);
HWND __fastcall unknown_create_dialog_5ff610(int, DLGPROC, int);
int __stdcall Wonline_Main_Dialog_007469c0(HWND, UINT, WPARAM, LPARAM);
bool __fastcall Get_Channel_List_0073d8f0();
bool __fastcall Request_Chat_Channel_List_0073dd20(bool wait);
int __fastcall Join_Selected_Lobby_00744930(bool unknown);
void __fastcall Initialize_WDT_Sounds_00752210();
void __fastcall Discard_WDT_Sound_List_00752890(WolStringArray sounds);
bool __fastcall End_Dialog_007357e0(HWND dialog, int result);
bool __fastcall Unknown_00514EE0();
// @ref ?wol_wait_events_b264f8@@3PAPAXA=00b264f8
// @ref ?connection_wait_callback_0073c120@@YA_NXZ=0073c120
// @ref ?wol_channel_list_label_007fd754@@3PADA=007fd754
// @ref ?wol_joining_label_7fe688@@3PADA=007fe688
// @ref ?wol_source_file_007fd62c@@3PADA=007fd62c
// @ref ?wol_login_complete_label_7fe694@@3PADA=007fe694
// @ref ?wol_motd_separator_7f3830@@3PADA=007f3830
// @ref ?wol_wide_newline_7e58ec@@3PAGA=007e58ec
// @ref ?unknown_wdt_sounds_initialized_b2ac28@@3_NA=00b2ac28
// @ref ?wol_lan_leave_b2abf0@@3HA=00b2abf0
// @ref ?unknown_7fd300@@3HA=007fd300
// @ref ?unknown_7fd354@@3_NA=007fd354
// @ref ?unknown_time_b2abd0@@3HA=00b2abd0
// @ref ?unknown_time_b2abd4@@3HA=00b2abd4
// @ref ?game_window_00b263d8@@3PAUHWND__@@A=00b263d8
// @ref ?Add_At@WolIntArray@@QAEDAAHH@Z=00766f90
// @ref ?End_Dialog_007357e0@@YI_NPAUHWND__@@H@Z=007357e0
// @ref ?Get_007662c0@?$WolArrayList@VWstring@@@@QAE_NAAVWstring@@H@Z=007662c0

inline void __fastcall Close_Wonline_Wait(unsigned int flags);

inline void Set_Wait_Dialog_Text(unsigned short const *text)
{
    HWND dialog = (HWND)Unknown_00735940(0xc4);
    if (dialog) {
        SendDlgItemMessageA(dialog, 0x5b2, 0x4b2, 0, (LPARAM)text);
    }
}

inline Wstring Narrow_Text(unsigned short const *text)
{
    WideString wide(text);
    return Narrow_Copy_00771280(wide);
}

inline WideString Wide_Text(char const *text)
{
    Wstring narrow(text);
    return Wstring_To_Wide(narrow);
}

inline void Print_Message_Of_The_Day()
{
    if (unknown_motd_b26954.Length() > 0) {
        char *text = new char[unknown_motd_b26954.Length() + 1];
        if (text) {
            strcpy(text, unknown_motd_b26954.Get());
            char *token = strtok(text, wol_motd_separator_7f3830);
            while (token) {
                WideString line = Wide_Text(token);
                Unknown_005C2C80(unknown_color_7a7360, line.Get());
                token = strtok(0, wol_motd_separator_7f3830);
            }
            Unknown_005C2C80(unknown_color_7a7360, wol_wide_newline_7e58ec);
            unknown_motd_b26954.Release();
            delete text;
        }
    }
}

inline DWORD Wait_For_Join_Event()
{
    DWORD event;
    while ((event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 100)) == 0x102) {
        Unknown_0073e100();
    }
    return event;
}
int __fastcall Unknown_00743720(HWND window, bool first_time)
{
    int result = 0;
    if (unknown_b2abd9 && unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2
        && unknown_session_a3d298.ScoreWinner != -1 && unknown_session_a3d298.ScoreWinner < 8) {
    Wstring winner = Narrow_Text((unsigned short const *)unknown_session_a3d298.Scores[unknown_session_a3d298.ScoreWinner].Name);
    if (_strnicmp(winner.Get(), unknown_name_a3d3a0, 0x14) == 0) {
        if (unknown_a3d3bc == 0) {
            Discard_WDT_Sound_List_00752890(unknown_strings_b26570);
        } else if (unknown_a3d3bc == 1) {
            Discard_WDT_Sound_List_00752890(unknown_strings_b26a50);
        }
    } else if (unknown_a3d3bc == 0) {
        Discard_WDT_Sound_List_00752890(unknown_strings_b29380);
    }
    }
    unknown_b2abd9 = false;
    unknown_b2ac40 = 0;
    if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2) {
        unknown_chat_a72cfc->unknown_slot45(unknown_a3d3bc);
        if (!unknown_wdt_sounds_initialized_b2ac28) {
            Initialize_WDT_Sounds_00752210();
        }
    }
    Unknown_00514EE0();
    if (unknown_b2abda) {
        int login = Login_Wonline_00742fd0();
        if (login != 1) {
            return login;
        }
    }
    int i;
    for (i = 0; i < 18; i++) {
        ResetEvent(wol_wait_events_b264f8[i]);
    }
    if (window == 0) {
        unknown_5159b0(0, true);
        window = unknown_create_dialog_5ff610(0x113, (DLGPROC)Wonline_Main_Dialog_007469c0, 0);
        Print_Message_Of_The_Day();
        {
            WideString title(StringTable::Load_String(wol_login_complete_label_7fe694, 0, wol_source_file_007fd62c, 0x2373));
            Open_Wait_Window_0074d4d0(0x10, title, false);
        }
    }
    unknown_query_count_b2abf4++;
    unknown_squad_query_b2abf8 = 1;
    unknown_chat_a72cfc->unknown_slot44(0);
    unknown_7fd300 = 0x21;
    Set_Wait_Dialog_Text(StringTable::Load_String(wol_channel_list_label_007fd754, 0, wol_source_file_007fd62c, 0x2384));
    if (!Request_Chat_Channel_List_0073dd20(true)) {
        goto cleanup;
    }
    Set_Wait_Dialog_Text(StringTable::Load_String(wol_joining_label_7fe688, 0, wol_source_file_007fd62c, 0x238b));
    {
        int joined = Join_Selected_Lobby_00744930(unknown_7fd354 && !first_time);
        unknown_7fd354 = true;
        if (joined == -1) {
            goto cleanup;
        }
    }
    {
        DWORD event = Wait_For_Join_Event();
        ResetEvent(wol_wait_events_b264f8[event]);
        if (event == 0 || event == 5) {
            goto logout;
        }
    }
    wol_lan_leave_b2abf0 = 0;
    PostMessageA(window, 0x593, 0, 0);
    Close_Wonline_Wait(~0u);
    SetFocus(game_window_00b263d8);
    ShowWindow(window, 1);
    SetFocus(window);
    SetFocus(GetDlgItem(window, 0x540));
    unknown_time_b2abd4 = 0;
    unknown_time_b2abd0 = time(0);
    for (;;) {
        DWORD event;
        while ((event = WaitForMultipleObjects(18, wol_wait_events_b264f8, 0, 20)) == 0x102) {
            Unknown_0073e100();
            if (wol_lan_leave_b2abf0) {
                EnableWindow(GetDlgItem(window, 0x53d), FALSE);
                EnableWindow(GetDlgItem(window, 0x6ee), FALSE);
                EnableWindow(GetDlgItem(window, 0x62d), FALSE);
                EnableWindow(GetDlgItem(window, 0x62b), FALSE);
                EnableWindow(GetDlgItem(window, 0x689), FALSE);
                EnableWindow(GetDlgItem(window, 0x558), FALSE);
                EnableWindow(GetDlgItem(window, 0x61f), FALSE);
                EnableWindow(GetDlgItem(window, 0x686), FALSE);
                if (Join_Selected_Lobby_00744930(false) == -1) {
                    EnableWindow(GetDlgItem(window, 0x686), TRUE);
                    SetEvent(wol_wait_events_b264f8[5]);
                } else {
                    PostMessageA(window, 0x593, 0, 0);
                }
                wol_lan_leave_b2abf0 = 0;
            }
        }
        ResetEvent(wol_wait_events_b264f8[event]);
        if (event == 0) {
            goto cleanup;
        }
        if (event != 6) {
            if (event == 15) {
                result = 2;
                break;
            }
            if (event == 5) {
                goto cleanup;
            }
            if (event == 7) {
                goto started;
            }
        } else {
            break;
        }
    }
    unknown_server_error_b2a8ec[0] = 0;
logout:
    End_Dialog_007357e0(window, 0);
    Unknown_0073e100();
    window = 0;
    if (unknown_chat_a72cfc) {
        unknown_chat_a72cfc->unknown_slot09();
    }
cleanup:
    Close_Wonline_Wait(~0u);
    Message_Box_005c3230(unknown_server_error_b2a8ec, 0, connection_wait_callback_0073c120, false);
    if (window) {
        End_Dialog_007357e0(window, 0);
    }
    while (End_Dialog_007357e0(0, 0)) {
    }
    if (result == 1) {
        unknown_b2abd9 = true;
    }
    if (unknown_game_mode_a3d298 == 4 && unknown_a3d2a4 == 2) {
        unknown_known_names_b294b8.Clear_Inline();
    }
    return result;
started:
    result = 1;
    unknown_chat_a72cfc->unknown_slot09();
    unknown_b2ac04 = false;
    unknown_server_error_b2a8ec[0] = 0;
    goto cleanup;
}
