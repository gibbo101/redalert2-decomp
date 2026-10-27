#include "shared/wol_sink.hpp"
HRESULT __stdcall CNetUtilEventSink::OnNewNick(HRESULT result, char const *message, char const *nick, char const *password)
{
    wchar_t error[5120];
    Debug_Printf("OnNewNick\n");
    unknown_newnick_result_b2ac08 = result;
    if (result == S_OK) {
        rc_ptr<PlayerProfile> profile = PlayerProfile::Load_00738880(nick);
        int nick_slot = 0;
        WolRegistryOptions options;
        options.Read_004ff200();
        if (options.unknown_004ff2c0()) {
            nick_slot = Save_Nickname_00745320(nick, password, true, profile->Unknown_Value_10());
            Save_Session_00670380(&unknown_session_a3d298);
        }
        bool login_dialog = true;
        bool alternate = false;
        HWND dialog = (HWND)Unknown_00735940(0x10f);
        if (!dialog) {
            dialog = (HWND)Unknown_00735940(0x11d);
            alternate = dialog != 0;
            if (!dialog) {
                login_dialog = false;
                dialog = (HWND)Unknown_00735940(0x114);
            }
        }
        if (dialog) {
            HWND list = GetDlgItem(dialog, 0x628);
            if (alternate) {
                SendMessageA(list, 0x4b4, 0, (LPARAM)nick);
            } else {
                int index = SendMessageA(list, 0x4bc, 0, (LPARAM)nick);
                SendMessageA(list, 0x151, index, nick_slot);
                SendMessageA(list, 0x14e, index, 0);
            }
            if (login_dialog) {
                unknown_wstring_b26cb8 = nick;
                unknown_password_b2a63c = password;
                HWND edit = GetDlgItem(dialog, 0x72c);
                SendMessageA(edit, 0x4b4, 0, (LPARAM)unknown_password_b2a63c.Peek_Buffer());
                unknown_7fd374 = true;
                EnableWindow(GetDlgItem(dialog, 0x539), true);
                if (!alternate) {
                    EnableWindow(GetDlgItem(dialog, 0x72d), false);
                    SendMessageA(GetDlgItem(dialog, 0x72d), 0xf1, 1, 0);
                }
            } else {
                SendMessageA(GetDlgItem(dialog, 0x6ff), 0xf1, 0, 0);
                EnableWindow(GetDlgItem(dialog, 0x6ff), true);
            }
            if (!alternate) {
                EnableWindow(GetDlgItem(dialog, 0x6eb), true);
                Wstring nickname(nick);
                profile->Populate_Dialog_00739b70(dialog, nickname, true);
            }
        }
    }
    if (message) {
        Unknown_006FA0C0(error, message, -1);
        Popup_005c3230(error, 0, Unknown_0073c120, 0);
    } else {
        Popup_005c3230(L"Unknown Status", 0, Unknown_0073c120, 0);
    }
    void *dialog = Unknown_00735940(0xc4);
    if (dialog && (unknown_b2abe0 &= ~0x100u) == 0) Unknown_007357E0(dialog, 0);
    HWND window = Unknown_00735B10();
    window = GetDlgItem(window, 0x540);
    if (window) SetFocus(window);
    return S_OK;
}
// @ref ?Load_00738880@PlayerProfile@@=00738880
// @ref ?Populate_Dialog_00739b70@PlayerProfile@@=00739b70
// @ref ?Read_004ff200@WolRegistryOptions@@=004ff200
// @ref ?unknown_004ff2c0@WolRegistryOptions@@=004ff2c0
// @ref ?unknown_session_a3d298=00a3d298
// @ref ?Save_Session_00670380=00670380
// @ref ?Save_Nickname_00745320=00745320
// @ref ?unknown_password_b2a63c=00b2a63c
// @ref ?unknown_newnick_result_b2ac08=00b2ac08
// @ref ?unknown_7fd374=007fd374
// @ref ?Unknown_0073c120=0073c120
// @ref ?Popup_005c3230=005c3230
// @ref ??_7?$rc_ptr@VPlayerProfile@@@@6B@=007af54c
// @ref ??1rc_ptr_base@@=00639510
// @ref ??_C@_0L@OKFM@OnNewNick?6?$AA@=007fdbac
// @ref ??_C@_1BO@MIJH@?$AAU?$AAn?$AAk?$AAn?$AAo?$AAw?$AAn?$AA?5?$AAS?$AAt?$AAa?$AAt?$AAu?$AAs?$AA?$AA@=007fdb8c
