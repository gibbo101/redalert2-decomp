// Login_Wonline 0x00742FD0: fetch the server list, try the stored auto-login, else run the login dialog.
#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/crt_string.hpp"
#include "shared/crt_memory.hpp"
#include "shared/wol_registry_options.hpp"
#include "shared/player_profile.hpp"
#include "shared/session_state.hpp"
#include "shared/dialog_create.hpp"
#include "shared/unknown_globals.hpp"
void __fastcall Open_Wait_Window_0074d4d0(unsigned int, WideString const &, bool);
int __fastcall Unknown_00751c30(unsigned int flags);
Wstring __fastcall WOL_Auto_Login_Persona();
Wstring __fastcall WOL_Last_Valid_Persona();
void __fastcall Unknown_007391f0(Wstring const &);
void __fastcall unknown_5159b0(int, bool);
void __fastcall unknown_517370(bool);
HWND __fastcall unknown_create_dialog_5ff610(int, DLGPROC, int);
void __fastcall unknown_dialog_5ff7c0(HWND);
void __fastcall unknown_dialog_5ff6e0(HWND);
int __fastcall Run_Control_Dialog_006011a0(int, DLGPROC, OwnerDraw::DialogControl *);
long __stdcall Wonline_Account_Dialog_007540a0(HWND, UINT, WPARAM, LPARAM);
long __stdcall Wonline_Dialog_00755070(HWND, UINT, WPARAM, LPARAM);
bool __fastcall Get_Auto_Login_00738cb0();
void Debug_Printf(char const *, ...);
void *__fastcall unknown_find_key_by_value(int value);
extern bool remember_password_b2ac74;
extern char wol_source_file_007fd62c[];
// @ref ??_C@_0BG@LPOE@TXT_FETCHING_SERVLIST?$AA@=007fe670
// @ref ?unknown_session_a3d298@@3UUnknownSessionState@@A=00a3d298
// @ref ?unknown_find_key_by_value@@YIPAXH@Z=00735940
// @ref ?Wonline_Dialog_00755070@@YGJPAUHWND__@@IIJ@Z=00755070

bool Unknown_00742d50();

// Fetch_Server_List, Set_Login_Focus and Remember_Login are level hypotheses (owner ruling 2026-11-05): their
// statements are visible in the body; the inline boundaries come from the expansion budget.
inline void Set_Login_Focus(HWND window)
{
    if (unknown_wstring_b26cb8.Length() > 0 && unknown_password_b2a63c.Length() == 0) {
        SetFocus(GetDlgItem(window, 0x72c));
    } else {
        SetFocus(GetDlgItem(window, 0x628));
    }
}

inline void Remember_Login(WolRegistryOptions &saved, rc_ptr<PlayerProfile> &profile)
{
    if (remember_password_b2ac74 && saved.unknown_004ff2c0()) {
        Save_Nickname_00745320(unknown_wstring_b26cb8.Get(), unknown_password_b2a63c.Get(), unknown_7fd374, profile->Unknown_Value_10());
        unknown_session_a3d298.Write_MultiPlayer_Settings();
    }
}

inline void Reset_WOL_Globals()
{
    memset(&unknown_game_channel_b299c0, 0, sizeof(WOL::Channel));
    memset(&unknown_pending_channel_b26a60, 0, sizeof(WOL::Channel));
    unknown_lobbies_b26c88.setEmpty();
    unknown_games_b29990.setEmpty();
    unknown_users_b2a728.setEmpty();
    unknown_b2abe8 = 0;
}

inline int Fetch_Server_List()
{
    {
        WideString title(StringTable::Load_String("TXT_FETCHING_SERVLIST", 0, wol_source_file_007fd62c, 0x56cc));
        Open_Wait_Window_0074d4d0(0x10, title, false);
    }
    unsigned int flags = 0x2300;
    if (unknown_a3d2a4 != 2) {
        flags = 0x2100;
    }
    return Unknown_00751c30(flags);
}

inline void __fastcall Close_Wonline_Wait(unsigned int flags);
int __fastcall Login_Wonline_00742fd0()
{
    bool failed = false;
    unknown_connection_result_b2ac10 = 0;
    int result = Unknown_00742390();
    if (result != 1) {
        return result;
    }
    {
        Reset_WOL_Globals();
        result = 0;
        int error = Fetch_Server_List();
        switch (error) {
        case 0:
            break;
        case 2:
            failed = true;
            result = -1;
            break;
        default:
            failed = true;
            result = -2;
            break;
        }
        WolRegistryOptions options;
        options.Read_004ff200();
        if (!failed) {
            if (options.unknown_004ff2b0()) {
                Wstring persona = WOL_Auto_Login_Persona();
                if (persona.Length() > 0) {
                    if (Recall_Stored_Login_00742d80(persona)) {
                        int index = -1;
                        if (Is_Online_Session()) {
                            rc_ptr<PlayerProfile> profile = PlayerProfile::Load_00738880(persona);
                            if (profile.Get()) {
                                index = Find_Server_Suffix_00742e30(profile->Get_Server());
                            }
                            if (index == -1) {
                                index = unknown_irc_index_b292d8;
                            }
                        } else {
                            rc_ptr<PlayerProfile> profile = PlayerProfile::Load_00738880(persona);
                            if (profile.Get()) {
                                if (profile->Server.Length() == 0) {
                                    index = unknown_irc_index_b292d8;
                                } else {
                                    index = Find_Server_Suffix_00742e30(profile->Get_Server());
                                }
                            }
                        }
                        if (index != -1) {
                            unknown_irc_index_b292d8 = index;
                            if (Unknown_00742d50()) {
                                return 1;
                            }
                            failed = Unknown_00742eb0();
                        }
                    }
                }
            }
            if (unknown_wstring_b26cb8.Length() == 0 && options.unknown_004ff2c0()) {
                unknown_wstring_b26cb8 = WOL_Last_Valid_Persona();
            }
            {
                Wstring empty((char const *)0x83c55c);
                Unknown_007391f0(empty);
            }
            if (failed) {
                return 0;
            }
            Debug_Printf((char const *)0x7fe65c);
            SimpleWonlineDialogControl control;
            int dialog_id = options.unknown_004ff2c0() ? 0x10f : 0x11d;
            unknown_5159b0(0, true);
            HWND window = unknown_create_dialog_5ff610(dialog_id, (DLGPROC)Wonline_Account_Dialog_007540a0, (int)&control);
            unknown_dialog_5ff7c0(window);
            Set_Login_Focus(window);
            while (!control.unknown_slot2() && !Unknown_0073e100() && !unknown_6000d0()) {
                unknown_517370(false);
            }
            unknown_dialog_5ff6e0(window);
            if ((int)control.Get_Window_00601180() == 2) {
                failed = true;
            } else {
                Unknown_0073e100();
                unknown_b2abd8 = false;
                WolRegistryOptions saved;
                saved.Read_004ff200();
                rc_ptr<PlayerProfile> profile;
                if (saved.unknown_004ff2c0()) {
                    profile = PlayerProfile::Load_00738880(unknown_wstring_b26cb8);
                } else {
                    profile.Set(unknown_profile_b28cc4);
                }
                int found = Find_Server_Suffix_00742e30(profile->Get_Server());
                if (found != -1) {
                    unknown_irc_index_b292d8 = found;
                }
                if (unknown_irc_index_b292d8 >= unknown_servers_b2a700.length()) {
                    unknown_irc_index_b292d8 = -1;
                }
                if (unknown_irc_index_b292d8 == -1 && unknown_servers_b2a700.length() > 1) {
                    unknown_irc_index_b292d8 = 1;
                }
                if (Unknown_00742d50()) {
                    Remember_Login(saved, profile);
                    if (!saved.unknown_004ff2b0() || !Get_Auto_Login_00738cb0()) { return 1; }
                    unknown_5159b0(0, true);
                    SimpleWonlineDialogControl next;
                    Run_Control_Dialog_006011a0(0x112, (DLGPROC)Wonline_Dialog_00755070, &next);
                    return 1;
                }
            }
        }
        Close_Wonline_Wait(~0u);
        if (!failed) {
            Unknown_00742eb0();
        }
        unknown_b2abd8 = true;
    }
    return result;
}
