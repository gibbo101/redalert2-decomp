// long __stdcall Wonline_Account_Dialog_007540a0(HWND window, UINT message, WPARAM wparam, LPARAM lparam) (0x007540A0)
#include "shared/wol_sink.hpp"
#include "shared/wonline_dialog_control.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/crt_string.hpp"
#include "shared/wol_registry_options.hpp"
#include "shared/crt_stdio.hpp"
int __fastcall unknown_dialog_proc_5ffb00(HWND,UINT,WPARAM,LPARAM);
void __fastcall unknown_dialog_5e5f20(HWND);
void __stdcall unknown_dialog_5ecf40(HWND,int);
void __fastcall unknown_reset_combo_6007f0(HWND);
LRESULT __fastcall unknown_get_window_text(HWND,Wstring &);
LRESULT __fastcall unknown_get_combo_item_text(HWND,WPARAM,Wstring &);
void __fastcall Unknown_00753240(HWND);
bool __fastcall Populate_Server_Choices_007454c0(HWND,bool);
void __fastcall Create_Wonline_Account_00744a00(HWND);
void __fastcall View_HTML_0073c580(char const *,int);
Wstring __fastcall WOL_Auto_Login_Persona();
Wstring __fastcall WOL_Last_Valid_Persona();
void __fastcall WOL_Set_Auto_Login_Persona(Wstring const &);
void __fastcall WOL_Set_Last_Valid_Persona(Wstring const &);
extern int profile_url_value_b2ac5c;
extern char profile_registration_url_7fd5a4[];
// @ref ?account_dialog_updating_b2aca8@@3_NA=00b2aca8
// @ref ?remember_password_b2ac74@@3_NA=00b2ac74
extern bool account_dialog_updating_b2aca8;
extern bool remember_password_b2ac74;

void *__fastcall unknown_find_key_by_value(int value);
// @ref ?unknown_find_key_by_value@@YIPAXH@Z=00735940

// Looks text up among the stored nicknames; a match becomes the current nickname and password.
inline bool Find_Stored_Nick(Wstring const &text)
{
    for (int nick_index = 1; nick_index <= 32; nick_index++) {
        char const *nickname, *password;
        if (unknown_chat_a72cfc->unknown_slot36(nick_index, &nickname, &password) == 0 && nickname != 0
            && strlen(nickname) > 0 && _stricmp(text.Peek_Buffer(), nickname) == 0) {
            unknown_wstring_b26cb8 = nickname;
            unknown_password_b2a63c = password;
            unknown_7fd374 = false;
            return true;
        }
    }
    unknown_wstring_b26cb8.Release();
    return false;
}

long __stdcall Wonline_Account_Dialog_007540a0(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
{
    if (message == 0x110 && lparam) SetWindowLongA(window, 8, *(long *)(lparam + 4));
    long result = unknown_dialog_proc_5ffb00(window, message, wparam, lparam);
    if (result) return result;
    OwnerDraw::DialogControl *control = (OwnerDraw::DialogControl *)GetWindowLongA(window, 8);
    switch (message) {
    case 0xf:
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window, 0);
        return 1;
    case 0x14:
        return 1;
    case 0x2b:
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:
        switch ((unsigned short)wparam) {
        case 0x539:
            control->Set_Window_006010f0((unsigned)window, (HWND)0x539);
            return 0;
        case 0x686:
            control->Set_Window_006010f0((unsigned)window, (HWND)2);
            return 0;
        case 0x628: {
            bool have_key = unknown_find_key_by_value(0x11d) != 0;
            switch ((unsigned short)(wparam >> 16)) {
            case 1: {
                if (have_key) break;
                account_dialog_updating_b2aca8 = true;
                unknown_wstring_b26cb8.Release();
                unknown_password_b2a63c.Release();
                unknown_7fd374 = true;
                HWND edit = GetDlgItem(window, 0x72c);
                SendMessageA(edit, 0x4b4, 0, (LPARAM)unknown_password_b2a63c.Peek_Buffer());
                bool remember = remember_password_b2ac74;
                int selected = SendMessageA((HWND)lparam, 0x147, 0, 0);
                if (selected != -1) {
                    int nick_index = SendMessageA((HWND)lparam, 0x150, selected, 0);
                    if (nick_index > 0 && nick_index <= 32) {
                        char const *nickname, *password;
                        unknown_get_combo_item_text((HWND)lparam, selected, unknown_wstring_b26cb8);
                        unknown_chat_a72cfc->unknown_slot36(nick_index, &nickname, &password);
                        unknown_password_b2a63c = password;
                        edit = GetDlgItem(window, 0x72c);
                        SendMessageA(edit, 0x4b4, 0, (LPARAM)unknown_password_b2a63c.Peek_Buffer());
                        unknown_7fd374 = false;
                        remember = true;
                    }
                }
                bool valid = unknown_wstring_b26cb8.Length() > 0 && unknown_password_b2a63c.Length() == 8;
                HWND check = GetDlgItem(window, 0x72d);
                SendMessageA(check, 0xf1, remember, 0);
                EnableWindow(check, 0);
                InvalidateRect(check, 0, 0);
                EnableWindow(GetDlgItem(window, 0x6eb), unknown_wstring_b26cb8.Length() > 0);
                EnableWindow(GetDlgItem(window, 0x539), valid);
                account_dialog_updating_b2aca8 = false;
                return 0;
            }
            case 5:
            case 0x300: {
                if ((unsigned short)(wparam >> 16) == 0x300 && !have_key) break;
                if ((unsigned short)(wparam >> 16) == 5 && have_key) break;
                if (account_dialog_updating_b2aca8) break;
                Wstring text;
                unknown_get_window_text((HWND)lparam, text);
                unknown_password_b2a63c.Release();
                bool match = Find_Stored_Nick(text);
                bool remember = match || remember_password_b2ac74;
                if (!match) {
                    unknown_wstring_b26cb8 = text;
                }
                account_dialog_updating_b2aca8 = true;
                HWND edit = GetDlgItem(window, 0x72c);
                SendMessageA(edit, 0x4b4, 0, (LPARAM)unknown_password_b2a63c.Peek_Buffer());
                InvalidateRect(edit, 0, 0);
                account_dialog_updating_b2aca8 = false;
                bool valid = unknown_wstring_b26cb8.Length() > 0 && unknown_password_b2a63c.Length() == 8;
                HWND check = GetDlgItem(window, 0x72d);
                ShowWindow(check, 0);
                SendMessageA(check, 0x49d, 0, 1);
                SendMessageA(check, 0xf1, remember, 0);
                EnableWindow(check, 0);
                SendMessageA(check, 0x49d, 0, 0);
                ShowWindow(check, 5);
                InvalidateRect(check, 0, 0);
                EnableWindow(GetDlgItem(window, 0x6eb), unknown_wstring_b26cb8.Length() > 0);
                EnableWindow(GetDlgItem(window, 0x539), valid);
                return 0;
            }
            }
            break;
        }
        case 0x629:
            if (unknown_find_key_by_value(0x11d) && unknown_profile_b28cc4) {
                Wstring server;
                unknown_get_window_text(GetDlgItem(window, 0x629), server);
                unknown_profile_b28cc4->Set_Server_00739920(server);
                return 0;
            }
            break;
        case 0x62a:
            if (unknown_find_key_by_value(0x11d) && unknown_profile_b28cc4) {
                HWND combo = GetDlgItem(window, 0x62a);
                int selected = SendMessageA(combo, 0x147, 0, 0);
                int locale = 0;
                if (selected != -1) {
                    locale = SendMessageA(combo, 0x150, selected, locale);
                }
                unknown_profile_b28cc4->Set_Locale_00739950(locale, 3);
                return 0;
            }
            break;
        case 0x6a1:
            if (unknown_find_key_by_value(0x11d) && unknown_profile_b28cc4) {
                int value = -2;
                HWND combo = GetDlgItem(window, 0x6a1);
                int selected = SendMessageA(combo, 0x147, 0, 0);
                if (selected != -1) value = SendMessageA(combo, 0x150, selected, 0);
                unknown_profile_b28cc4->Set_Country_007399b0(value);
                return 0;
            }
            break;
        case 0x6a2:
            if (unknown_find_key_by_value(0x11d) && unknown_profile_b28cc4) {
                int value = -2;
                HWND combo = GetDlgItem(window, 0x6a2);
                int selected = SendMessageA(combo, 0x147, 0, 0);
                if (selected != -1) value = SendMessageA(combo, 0x150, selected, 0);
                unknown_profile_b28cc4->Set_Color_007399d0(value);
                return 0;
            }
            break;
        case 0x72c:
            if ((unsigned short)(wparam >> 16) == 0x300 && !account_dialog_updating_b2aca8) {
                unknown_7fd374 = true;
                unknown_get_window_text((HWND)lparam, unknown_password_b2a63c);
                Wstring text;
                unknown_get_window_text(GetDlgItem(window, 0x628), text);
                bool valid = text.Length() > 0 && unknown_password_b2a63c.Length() == 8;
                HWND check = GetDlgItem(window, 0x72d);
                SendMessageA(check, 0x49d, 0, 1);
                EnableWindow(check, valid);
                InvalidateRect(check, 0, 0);
                SendMessageA(check, 0x49d, 0, 0);
                EnableWindow(GetDlgItem(window, 0x6eb), 0);
                EnableWindow(GetDlgItem(window, 0x539), valid);
                return 0;
            }
            break;
        case 0x72d:
            remember_password_b2ac74 = SendMessageA((HWND)lparam, 0xf0, 0, 0) == 1;
            return 0;
        case 0x6eb: {
            account_dialog_updating_b2aca8 = true;
            HWND nicknames = GetDlgItem(window, 0x628);
            int selected = SendMessageA(nicknames, 0x4b9, -1, (LPARAM)unknown_wstring_b26cb8.Peek_Buffer());
            if (selected != -1) {
                Wstring nickname;
                unknown_get_combo_item_text(nicknames, selected, nickname);
                nickname.To_Lower();
                Wstring automatic = WOL_Auto_Login_Persona();
                if (nickname == automatic.As_Lower()) {
                    WOL_Set_Auto_Login_Persona(unknown_string_83c55c);
                }
                Wstring last = WOL_Last_Valid_Persona();
                if (nickname == last.As_Lower()) {
                    WOL_Set_Last_Valid_Persona(unknown_string_83c55c);
                }
                int nick_index = SendMessageA(nicknames, 0x150, selected, 0);
                SendMessageA(nicknames, 0x144, selected, 0);
                unknown_chat_a72cfc->unknown_slot37(nick_index, unknown_string_83c55c, unknown_string_83c55c, 1);
            }
            SendMessageA(nicknames, 0x4b4, 0, (LPARAM)unknown_string_83c55c);
            InvalidateRect(nicknames, 0, 0);
            HWND edit = GetDlgItem(window, 0x72c);
            SendMessageA(edit, 0x4b4, 0, (LPARAM)unknown_string_83c55c);
            unknown_wstring_b26cb8.Release();
            unknown_password_b2a63c.Release();
            unknown_7fd374 = true;
            HWND check = GetDlgItem(window, 0x72d);
            EnableWindow(check, 0);
            InvalidateRect(check, 0, 0);
            EnableWindow(GetDlgItem(window, 0x6eb), 0);
            EnableWindow(GetDlgItem(window, 0x539), 0);
            account_dialog_updating_b2aca8 = false;
            return 0;
        }
        case 0x6ea:
            Create_Wonline_Account_00744a00(window);
            return 0;
        case 0x6ec: {
            char url[256];
            sprintf(url, profile_registration_url_7fd5a4, profile_url_value_b2ac5c);
            View_HTML_0073c580(url, 0);
            return 0;
        }
        }
        break;
    case 0x497: {
        account_dialog_updating_b2aca8 = true;
        HWND nicknames = GetDlgItem(window, 0x628);
        HWND edit = GetDlgItem(window, 0x72c);
        SendMessageA(nicknames, 0x4d1, 1, 0);
        SendMessageA(edit, 0x4d1, 1, 0);
        SendMessageA(nicknames, 0xc5, 9, 0);
        SendMessageA(edit, 0xc5, 8, 0);
        unknown_reset_combo_6007f0(nicknames);
        SendMessageA(nicknames, 0x141, 9, 0);
        for (int nick_index = 1; nick_index < 32; nick_index++) {
            char const *nickname, *password;
            if (unknown_chat_a72cfc->unknown_slot36(nick_index, &nickname, &password) == 0 && nickname != 0 && strlen(nickname) > 0) {
                int entry = SendMessageA(nicknames, 0x4bc, 0, (LPARAM)nickname);
                SendMessageA(nicknames, 0x151, entry, nick_index);
            }
        }
        Wstring saved(unknown_wstring_b26cb8);
        unknown_password_b2a63c.Release();
        bool remember = Find_Stored_Nick(unknown_wstring_b26cb8);
        if (!remember) {
            unknown_wstring_b26cb8 = saved;
        }
        SendMessageA(nicknames, 0x4b4, 0, (LPARAM)unknown_wstring_b26cb8.Peek_Buffer());
        if (unknown_wstring_b26cb8.Length() > 0) {
            SendMessageA(edit, 0x4b4, 0, (LPARAM)unknown_password_b2a63c.Peek_Buffer());
            unknown_7fd374 = false;
        }
        bool valid = unknown_wstring_b26cb8.Length() > 0 && unknown_password_b2a63c.Length() == 8;
        HWND check = GetDlgItem(window, 0x72d);
        SendMessageA(check, 0x49d, 0, 1);
        SendMessageA(check, 0xf1, remember, 0);
        EnableWindow(check, 0);
        InvalidateRect(check, 0, 0);
        SendMessageA(check, 0x49d, 0, 0);
        EnableWindow(GetDlgItem(window, 0x6eb), unknown_wstring_b26cb8.Length() > 0);
        EnableWindow(GetDlgItem(window, 0x539), valid);
        WolRegistryOptions options;
        options.Read_004ff200();
        if (!options.unknown_004ff2c0()) {
            Unknown_00753240(GetDlgItem(window, 0x62a));
            Fill_Side_Combo_4d1560(window, 0x6a1);
            HWND sides = GetDlgItem(window, 0x6a1);
            int count = SendMessageA(sides, 0x146, 0, 0);
            int index;
            for (index = 0; index < count; index++) {
                if (SendMessageA(sides, 0x150, index, 0) == unknown_profile_b28cc4->Country) {
                    SendMessageA(sides, 0x14e, index, 0);
                    break;
                }
            }
            Init_Color_Entries_4d1ea0();
            Fill_Color_Combo_4d2080(window, 0x6a2);
            HWND colors = GetDlgItem(window, 0x6a2);
            int count2 = SendMessageA(colors, 0x146, 0, 0);
            for (index = 0; index < count2; index++) {
                if (SendMessageA(colors, 0x150, index, 0) == unknown_profile_b28cc4->Color) {
                    SendMessageA(colors, 0x14e, index, 0);
                    break;
                }
            }
            Populate_Server_Choices_007454c0(GetDlgItem(window, 0x629), true);
        }
        account_dialog_updating_b2aca8 = false;
        return 0;
    }
    case 0x4da: {
        unknown_get_window_text(GetDlgItem(window, 0x72c), unknown_password_b2a63c);
        Wstring text;
        unknown_get_window_text(GetDlgItem(window, 0x628), text);
        if (text.Length() > 0 && unknown_password_b2a63c.Length() == 8) {
            PostMessageA(GetDlgItem(window, 0x539), 0xf5, 0, 0);
        }
        break;
    }
    case 0x4db: {
        bool flag = wparam != 0;
        HWND child = (HWND)lparam;
        HWND parent = GetParent(child);
        while (parent != 0) {
            if (child == 0) return 0;
            if (parent == window) break;
            child = parent;
            parent = GetParent(child);
        }
        if (child != 0) Unknown_005def80((long)child, flag);
        break;
    }
    case 0x4ed:
        ShowWindow(window, 0);
        unknown_dialog_5ecf40(window, 1);
        break;
    }
    return 0;
}
