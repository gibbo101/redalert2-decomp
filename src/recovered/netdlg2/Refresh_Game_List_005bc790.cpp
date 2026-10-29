// void __fastcall Refresh_Game_List_005bc790() (0x005BC790)
#include "shared/lobby.hpp"
#include "shared/ipx_manager.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_09KODH@TXT_LOBBY?$AA@=007e6a28
// @ref ??_C@_0BC@CGNO@TXT_THATGUYS_GAME?$AA@=007e6a14
// @ref ??_C@_0BD@ELLL@D?3?2Ra2?2netdlg2?4cpp?$AA@=007e69c8
// @ref ??_C@_0BK@HKKP@TXT_THATGUYS_GAME_BRACKET?$AA@=007e69f8
// @ref ?Unknown_005c01d0@@YIXHHHH@Z=005c01d0
// @ref ?unknown_game_index_a71e90@@3HA=00a71e90
// @ref ?unknown_games_a3fa64@@3V?$DynamicVectorClass@PAUNodeNameType@@@@A=00a3fa64

void __fastcall Refresh_Game_List_005bc790()
{
    wchar_t text[80];

    if (Current_Dialog_Id_00735b20() == 0xBB) {
        HWND dialog = Unknown_00735B10();
        HWND list = GetDlgItem(dialog, 0x549);
        if (unknown_game_index_a71e90 >= unknown_games_a3fa64.Count()) {
            unknown_game_index_a71e90 = unknown_games_a3fa64.Count() - 1;
            Unknown_005c01d0(0, 1, 0, 0);
        }
        if (unknown_game_index_a71e90 < 0) {
            unknown_game_index_a71e90 = 0;
        }
        int top = SendDlgItemMessageA(dialog, 0x549, 0x18E, 0, 0);
        SendDlgItemMessageA(dialog, 0x549, 0x49D, 0, 1);
        SendMessageA(list, 0x184, 0, 0);
        SendMessageA(list, 0x4CD, 0, (LPARAM)StringTable::Load_String("TXT_LOBBY", 0, "D:\\Ra2\\netdlg2.cpp", 490));
        for (int i = 1; i < unknown_games_a3fa64.Count(); i++) {
            if (unknown_games_a3fa64[i]->Game.IsOpen) {
                swprintf(text, StringTable::Load_String("TXT_THATGUYS_GAME", 0, "D:\\Ra2\\netdlg2.cpp", 496), unknown_games_a3fa64[i]->Name);
            } else {
                swprintf(text, StringTable::Load_String("TXT_THATGUYS_GAME_BRACKET", 0, "D:\\Ra2\\netdlg2.cpp", 498), unknown_games_a3fa64[i]->Name);
            }
            SendMessageA(list, 0x4CD, 0, (LPARAM)text);
        }
        SendDlgItemMessageA(dialog, 0x549, 0x186, unknown_game_index_a71e90, 0);
        SendDlgItemMessageA(dialog, 0x549, 0x197, top, 0);
        SendDlgItemMessageA(dialog, 0x549, 0x49D, 0, 0);
        list = GetDlgItem(dialog, 0x549);
        InvalidateRect(list, 0, 0);
        UpdateWindow(list);
    }
}
