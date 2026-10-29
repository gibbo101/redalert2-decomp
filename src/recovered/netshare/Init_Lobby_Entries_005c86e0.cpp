// void __fastcall Init_Lobby_Entries_005c86e0() (0x005C86E0)
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_08DBAJ@GUI?3Open?$AA@=007e72ec
// @ref ??_C@_0L@DIEP@GUI?3Closed?$AA@=007e72e0
// @ref ??_C@_0L@JIHB@GUI?3AIEasy?$AA@=007e72d4
// @ref ??_C@_0N@GOPO@GUI?3AINormal?$AA@=007e72c4
// @ref ??_C@_0L@OJFC@GUI?3AIHard?$AA@=007e72b8
// @ref ??_C@_0M@NKFP@GUI?3Waiting?$AA@=007e72ac
// @ref ??_C@_0BB@JHBN@GUI?3OpenObserver?$AA@=007e7298
// @ref ?unknown_lobby_texts_a72d0c@@3PAPBGA=00a72d0c
// @ref ??_C@_0BE@EJOA@D?3?2Ra2?2netshare?4cpp?$AA@=007e6ebc

void __fastcall Init_Lobby_Entries_005c86e0()
{
    if (unknown_lobby_texts_a72d0c[0] == 0) {
        unknown_lobby_texts_a72d0c[0] = StringTable::Load_String("GUI:Open", 0, "D:\\Ra2\\netshare.cpp", 0xe98);
        unknown_lobby_texts_a72d0c[1] = StringTable::Load_String("GUI:Closed", 0, "D:\\Ra2\\netshare.cpp", 0xe99);
        unknown_lobby_texts_a72d0c[2] = StringTable::Load_String("GUI:AIEasy", 0, "D:\\Ra2\\netshare.cpp", 0xe9a);
        unknown_lobby_texts_a72d0c[3] = StringTable::Load_String("GUI:AINormal", 0, "D:\\Ra2\\netshare.cpp", 0xe9b);
        unknown_lobby_texts_a72d0c[4] = StringTable::Load_String("GUI:AIHard", 0, "D:\\Ra2\\netshare.cpp", 0xe9c);
        unknown_lobby_texts_a72d0c[5] = StringTable::Load_String("GUI:Waiting", 0, "D:\\Ra2\\netshare.cpp", 0xe9d);
        unknown_lobby_texts_a72d0c[6] = StringTable::Load_String("GUI:OpenObserver", 0, "D:\\Ra2\\netshare.cpp", 0xe9e);
    }
    if (unknown_open_entry_a72d2c == 0) {
        unknown_open_entry_a72d2c = new NodeNameType;
        wcscpy(unknown_open_entry_a72d2c->Name, unknown_lobby_texts_a72d0c[0]);
    }
    if (unknown_closed_entry_a72d30 == 0) {
        unknown_closed_entry_a72d30 = new NodeNameType;
        wcscpy(unknown_closed_entry_a72d30->Name, unknown_lobby_texts_a72d0c[1]);
    }
    if (unknown_easy_ai_entry_a72d34 == 0) {
        unknown_easy_ai_entry_a72d34 = new NodeNameType;
        wcscpy(unknown_easy_ai_entry_a72d34->Name, unknown_lobby_texts_a72d0c[2]);
    }
    if (unknown_medium_ai_entry_a72d38 == 0) {
        unknown_medium_ai_entry_a72d38 = new NodeNameType;
        wcscpy(unknown_medium_ai_entry_a72d38->Name, unknown_lobby_texts_a72d0c[3]);
    }
    if (unknown_hard_ai_entry_a72d3c == 0) {
        unknown_hard_ai_entry_a72d3c = new NodeNameType;
        wcscpy(unknown_hard_ai_entry_a72d3c->Name, unknown_lobby_texts_a72d0c[4]);
    }
    if (unknown_waiting_entry_a72d40 == 0) {
        unknown_waiting_entry_a72d40 = new NodeNameType;
        wcscpy(unknown_waiting_entry_a72d40->Name, unknown_lobby_texts_a72d0c[5]);
    }
    if (unknown_player_a72d44 == 0) {
        unknown_player_a72d44 = new NodeNameType;
        wcscpy(unknown_player_a72d44->Name, unknown_lobby_texts_a72d0c[6]);
    }
}
