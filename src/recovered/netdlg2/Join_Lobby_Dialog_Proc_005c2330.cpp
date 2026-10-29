// long __stdcall Join_Lobby_Dialog_Proc_005c2330(HWND window, unsigned message, unsigned wparam, long lparam) (0x005C2330)
// The joined player's game lobby dialog procedure.
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
#include "shared/modem_host.hpp"
#include "shared/wol_sink.hpp"
#include "shared/skirmish.hpp"
#include "shared/map_preview.hpp"
#include "shared/progress_screen.hpp"
#include "shared/campaign_score.hpp"
#include "shared/options_dialog.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_02ONAI@A1?$AA@=007e6d74
// @ref ??_C@_06IMK@R?$CFd?0?$CFd?$AA@=007e6d6c
// @ref ??_C@_11LOCGONAA@?$AA?$AA@=00839d4c
// @ref ?Unknown_005e22b0@@YIPBDPAUHWND__@@0@Z=005e22b0
// @ref ?Unknown_005c3d90@@YIXPBD0@Z=005c3d90
// @ref ?Unknown_005e8710@@YIXPAUHWND__@@@Z=005e8710
// @ref ?unknown_a72d52@@3_NA=00a72d52
// @ref ?unknown_lobby_result_a71e8c@@3HA=00a71e8c
// @ref ?ProgressScreen@@3VProgressScreenClass@@A=00a769e8
// @ref __imp__ChildWindowFromPointEx@16=0079a3a4
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??1UnknownPreview_0061D430@@QAE@XZ=0061d440

long __stdcall Join_Lobby_Dialog_Proc_005c2330(HWND window, unsigned message, unsigned wparam, long lparam)
{
    switch (message) {
    case 0x02:                  // WM_DESTROY
        if (ProgressScreen.Has_Window()) {
            ProgressScreen.Clear_Window();
        }
        if (unknown_dialog_preview_a72ce8 != 0) {
            delete unknown_dialog_preview_a72ce8;
            unknown_dialog_preview_a72ce8 = 0;
            return 0;
        }
        break;
    case 0x2B:                  // WM_DRAWITEM
        Unknown_005FE380(lparam);
        // fall through
    case 0x14:                  // WM_ERASEBKGND
        return 1;
    case 0x0F:                  // WM_PAINT
        Unknown_005FEE70(window);
        if (unknown_dialog_preview_a72ce8 != 0) {
            unknown_dialog_preview_a72ce8->Draw_0061D460(window);
        }
        if (ProgressScreen.Has_Window()) {
            ProgressScreen.Draw_It(Point2D(-1, -1));
        }
        unknown_dialog_5e5f20(window);
        ValidateRect(window, 0);
        return 0;
    case 0x84: {                // WM_NCHITTEST: the tool tip of the control under the cursor
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
                    text = StringTable::Load_String(label, 0, "D:\\Ra2\\netdlg2.cpp", 3143);
                }
            }
            SendMessageA(tip, 0x4B2, 0, (LPARAM)text);
            return 0;
        }
        break;
    }
    case 0x111:                 // WM_COMMAND
        switch ((unsigned short)wparam) {
        case 2:
            if (!unknown_lock_a71e98) {
                unknown_lobby_result_a71e8c = 2;
                return 0;
            }
            break;
        case 0x510:
        case 0x513:
        case 0x514:
        case 0x51E:
        case 0x51F:
        case 0x520:
        case 0x521:
        case 0x522:
        case 0x523:
        case 0x524:
        case 0x525:
        case 0x526:
        case 0x527:
        case 0x528:
        case 0x6A1:
        case 0x6A2:
            if ((unsigned short)(wparam >> 16) == 1) {
                int id = (unsigned short)wparam;
                int side_player = Side_Combo_Player_4d13b0(id);
                int color_player = Color_Combo_Player_4d1d10(id);
                int player = side_player > color_player ? side_player : color_player;
                int side_id = Player_Side_Combo_ID_4d1350(player);
                int color_id = Player_Color_Combo_ID_4d1cb0(player);
                if (player == side_player) {
                    Set_Slot_Country_005c9a10(window, side_id);
                } else {
                    Set_Slot_Color_005c9ab0(window, color_id);
                }
                char text[64];
                int side = Side_Combo_Data_4d1c70(window, side_id, -1);
                int color = Color_Combo_Data_4d2900(window, color_id, -1);
                sprintf(text, "R%d,%d", side, color);
                Unknown_005c3d90(Unknown_006FA120(unknown_host_name_a3f618), text);
                return 0;
            }
            break;
        case 0x540:
            Limit_Name_Text_005ccf50((HWND)lparam);
            if ((unsigned short)(wparam >> 16) == 0x501) {
                Send_Chat_Message_005bee20(window, unknown_color_7a737c, unknown_color_7a7364);
                return 0;
            }
            break;
        case 0x59F:
            if (unknown_players_a3fa7c.Count() != 0) {
                unknown_players_a3fa7c[0]->unknown_67 = 1;
                char text[64];
                sprintf(text, "A1");
                Send_Game_Options_005c3c60(text);
                Unknown_005cd030(window, false);
                HWND button = GetDlgItem(window, 0x59F);
                EnableWindow(button, FALSE);
                InvalidateRect(button, 0, FALSE);
                SendMessageA(button, 0x4DC, 0, 0);
                Unknown_005bbdd0(false);
                return 0;
            }
            break;
        }
        break;
    case 0x497:
        Fill_Side_Combos_4d16d0(window);
        Init_Color_Entries_4d1ea0();
        Fill_Color_Combos_4d2300(window);
        Lock_Slots_005c9da0(window, unknown_lobby_a3fa94);
        Select_Player_Side_4d1820(window, unknown_lobby_a3fa94);
        Select_Player_Color_4d23c0(window, unknown_lobby_a3fa94);
        EnableWindow(GetDlgItem(window, 0x59F), FALSE);
        unknown_a72d52 = false;
        Set_Player_Value_005bcbc0(0, 0);
        Unknown_005bbdd0(false);
        Refresh_Game_List_005bc790();
        Unknown_Fill_Options_Dialog_005c3550(window, 1);
        Select_Scenario_005c7c30(-1);
        unknown_int_a3db1c = 8;
        return 0;
    case 0x4E9: {               // the tool tip text of a combo box item
        ToolTipTextRequest *request = (ToolTipTextRequest *)lparam;
        request->Text = 0;
        if (request->Window != 0 && request->Item != -1) {
            int id = GetDlgCtrlID(request->Window);
            if (Control_Slot_005c9800(id) == -1) {
                if (Side_Combo_Player_4d13b0(id) == -1) {
                    if (Color_Combo_Player_4d1d10(id) != -1) {
                        request->Text = Color_Name_4d1d80(Color_Combo_Data_4d2900(window, id, request->Item));
                        return 1;
                    }
                } else {
                    int side = Side_Combo_Data_4d1c70(window, id, request->Item);
                    if (side != -1) {
                        request->Text = Side_Name_4d1420(side);
                        return 1;
                    }
                }
            } else {
                request->Text = Entry_Type_Name_005c9870((NodeNameType *)unknown_combo_selected_data_005c99d0(window, id, request->Item));
            }
        }
        return 1;
    }
    case 0x4EC:
        Unknown_005e8710(window);
        break;
    }
    return 0;
}
