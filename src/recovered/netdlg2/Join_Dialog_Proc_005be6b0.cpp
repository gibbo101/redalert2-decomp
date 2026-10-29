// long __stdcall Join_Dialog_Proc_005be6b0(HWND window, unsigned message, unsigned wparam, long lparam) (0x005BE6B0)
// The LAN join dialog's procedure (from Red Alert's Net_Join_Dialog).
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/modem_host.hpp"
#include "shared/wol_sink.hpp"
#include "shared/campaign_score.hpp"
#include "shared/string_table.hpp"
#include "shared/wol_settings.hpp"
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_11LOCGONAA@?$AA?$AA@=00839d4c
// @ref ??_C@_13JKDK@?$AA?0?$AA?$AA@=007e5c64
// @ref ?Unknown_005e22b0@@YIPBDPAUHWND__@@0@Z=005e22b0
// @ref ?Unknown_005e8710@@YIXPAUHWND__@@@Z=005e8710
// @ref ?Unknown_005def80@@YI_NJ_N@Z=005def80
// @ref ?unknown_lobby_result_a71e8c@@3HA=00a71e8c
// @ref ?unknown_join_list_7e699c@@3_NA=007e699c
// @ref ?unknown_a71e99@@3_NA=00a71e99
// @ref __imp__ChildWindowFromPointEx@16=0079a3a4
// @ref __imp__IsWindowEnabled@4=0079a3b0
// @ref ??2@YAPAXI@Z=00782017

long __stdcall Join_Dialog_Proc_005be6b0(HWND window, unsigned message, unsigned wparam, long lparam)
{
    switch (message) {
    case 0x14:                  // WM_ERASEBKGND
        return 1;
    case 0x0F:                  // WM_PAINT
        Unknown_005FEE70(window);
        unknown_dialog_5e5f20(window);
        ValidateRect(window, 0);
        return 0;
    case 0x2B:                  // WM_DRAWITEM
        Unknown_005FE380(lparam);
        return 1;
    case 0x111:                 // WM_COMMAND
        switch ((unsigned short)wparam) {
        case 0x549:             // the game list
            if (unknown_join_state_a71e94 <= 0) {
                int old_index = unknown_game_index_a71e90;
                int index = SendDlgItemMessageA(window, 0x549, 0x188, 0, 0);
                if (index >= 0 && unknown_join_list_7e699c) {
                    unknown_game_index_a71e90 = index;
                    wcscpy(unknown_host_name_a3f618, unknown_games_a3fa64[index]->Name);
                }
                if ((unsigned short)(wparam >> 16) == 1) {
                    Free_Pointers_005a7480(&unknown_players_a3fa7c);
                    if (old_index != unknown_game_index_a71e90) {
                        Unknown_005c01d0(1, 1, 1, 0);
                    }
                    Unknown_005bbdd0(false);
                    return 0;
                }
                if ((unsigned short)(wparam >> 16) == 2) {
                    unknown_lobby_result_a71e8c = unknown_a72c68 == 1 ? 0x6CE : 0x6CD;
                    return 0;
                }
            }
            break;
        case 0x541:             // the name edit
            if (IsWindowEnabled(window) && unknown_lobby_result_a71e8c == 0) {
                wchar_t name[20];
                name[0] = 0;
                HWND edit = GetDlgItem(window, 0x541);
                SendMessageA(edit, 0x4B3, 20, (LPARAM)name);
                wchar_t *text = name;
                while (*text != 0 && *text == ' ') {
                    text++;
                }
                if (*text == 0 && name[0] != 0) {
                    name[0] = 0;
                    edit = GetDlgItem(window, 0x541);
                    SendMessageA(edit, 0x4B2, 0, (LPARAM)name);
                }
                if (strcmp(Unknown_006FA120(name), unknown_name_a3d3a0) != 0) {
                    strcpy(unknown_name_a3d3a0, Unknown_006FA120(name));
                    Unknown_005c01d0(0, 0, 1, 0);
                    Unknown_005bbdd0(false);
                    return 0;
                }
            }
            break;
        case 0x540:             // the chat line
            Limit_Name_Text_005ccf50((HWND)lparam);
            if ((unsigned short)(wparam >> 16) == 0x501) {
                Send_Chat_Message_005bee20(window, unknown_color_7a737c, unknown_color_7a7364);
                return 0;
            }
            break;
        case 0x5C0:
            unknown_lobby_result_a71e8c = 0x5C0;
            Unknown_005CD3A0();
            return 0;
        case 0x6CC:
            unknown_lobby_result_a71e8c = (unsigned short)wparam;
            unknown_a71e99 = unknown_a72c68 == 1;
            return 0;
        case 0x6CD:
        case 0x6CE: {
            EnableWindow(window, FALSE);
            HWND edit = GetDlgItem(window, 0x541);
            if (edit != 0) {
                EnableWindow(edit, FALSE);
            }
            unknown_lobby_result_a71e8c = (unsigned short)wparam;
            return 0;
        }
        case 0x75F:
        case 0x760: {           // the observer radio buttons
            int checked = 0;
            HWND button = GetDlgItem(window, 0x760);
            if (button != 0) {
                checked = SendMessageA(button, 0xF0, 0, 0);
            }
            if ((unsigned short)wparam == 0x75F) {
                checked = checked == 0;
            }
            unknown_a72c68 = checked;
            Unknown_005cd540(0);
            return 0;
        }
        }
        break;
    case 0x200: {               // WM_MOUSEMOVE: the tool tip of the control under the cursor
        HWND tip = GetDlgItem(window, 0x695);
        if (tip != 0) {
            POINT point;
            point.x = lparam & 0xFFFF;
            point.y = (unsigned long)lparam >> 16;
            RECT rect;
            GetWindowRect(window, &rect);
            point.x -= rect.left;
            point.y -= rect.top;
            wchar_t const *text = L"";
            HWND control = ChildWindowFromPointEx(window, point, 1);
            if (control != 0) {
                char const *label = Unknown_005e22b0(window, control);
                if (label != 0) {
                    text = StringTable::Load_String(label, 0, "D:\\Ra2\\netdlg2.cpp", 2285);
                }
            }
            SendMessageA(tip, 0x4B2, 0, (LPARAM)text);
            return 0;
        }
        break;
    }
    case 0x497: {
        unknown_game_index_a71e90 = 0;
        unknown_join_list_7e699c = true;
        Unknown_005cd540(window);
        SendDlgItemMessageA(window, 0x541, 0xC5, 16, 0);
        SendDlgItemMessageA(window, 0x541, 0x4EB, 0, (LPARAM)L",");
        SendDlgItemMessageA(window, 0x541, 0x4D1, 1, 0);
        wchar_t *name = Unknown_006FA180(unknown_name_a3d3a0);
        HWND edit = GetDlgItem(window, 0x541);
        SendMessageA(edit, 0x4B2, 0, (LPARAM)name);
        unknown_map_name_a3d342[0] = 0;
        unknown_a3d3b4 = unknown_session_a3d298.unknown_12c;
        unknown_session_a3d298.unknown_120 = unknown_session_a3d298.unknown_130;
        Free_Pointers_005a7480(&unknown_games_a3fa64);
        Free_Pointers_005a7480(&unknown_players_a3fa7c);
        Free_Pointers_005a7480(&unknown_chat_a3fa4c);
        NodeNameType *node = new NodeNameType;
        wcscpy(node->Name, Unknown_006FA180(unknown_name_a3d3a0));
        node->Chat.LastTime = 0;
        node->Chat.LastChance = 0;
        node->Chat.Color = unknown_gpacket_a3f640.Chat.Color;
        unknown_chat_a3fa4c.Add(node);
        node = new NodeNameType;
        wcscpy(node->Name, L"");
        node->Game.IsOpen = 0;
        node->Game.LastTime = 0;
        unknown_games_a3fa64.Add(node);
        Unknown_005c01d0(1, 0, 1, 1);
        Refresh_Game_List_005bc790();
        Unknown_005bbdd0(false);
        Unknown_005FEE70(window);
        SetFocus(GetDlgItem(window, 0x540));
        break;
    }
    case 0x4DB:
        Unknown_005def80(lparam, wparam != 0);
        return 0;
    case 0x4EC:
        Unknown_005e8710(window);
        return 0;
    }
    return 0;
}
