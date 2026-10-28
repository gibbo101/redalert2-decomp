// UnknownPlayerEntry *__fastcall Unknown_Find_Lobby_Name_005c8b20(wchar_t const *name) (0x005C8B20)
// Finds the lobby buffer (the seven fixed ones, then the session nodes' names)
// whose text equals name (0x007837D3 compares wide strings, 0 when equal);
// null when there is none.
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUUnknownPlayerEntry@@A=00a72d44
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUUnknownPlayerEntry@@A=00a72d2c
// @ref ?Compare_Wide_007837d3@@YAHPBG0@Z=007837d3

UnknownPlayerEntry *__fastcall Unknown_Find_Lobby_Name_005c8b20(wchar_t const *name)
{
    if (Compare_Wide_007837d3(unknown_lobby_entries_a72d2c[0]->Name, name) == 0) {
        return unknown_lobby_entries_a72d2c[0];
    }
    if (Compare_Wide_007837d3(unknown_lobby_entries_a72d2c[1]->Name, name) == 0) {
        return unknown_lobby_entries_a72d2c[1];
    }
    if (Compare_Wide_007837d3(unknown_lobby_entries_a72d2c[2]->Name, name) == 0) {
        return unknown_lobby_entries_a72d2c[2];
    }
    if (Compare_Wide_007837d3(unknown_lobby_entries_a72d2c[3]->Name, name) == 0) {
        return unknown_lobby_entries_a72d2c[3];
    }
    if (Compare_Wide_007837d3(unknown_lobby_entries_a72d2c[4]->Name, name) == 0) {
        return unknown_lobby_entries_a72d2c[4];
    }
    if (Compare_Wide_007837d3(unknown_lobby_entries_a72d2c[5]->Name, name) == 0) {
        return unknown_lobby_entries_a72d2c[5];
    }
    if (Compare_Wide_007837d3(unknown_player_a72d44->Name, name) == 0) {
        return unknown_player_a72d44;
    }
    int count = unknown_players_a3fa7c.Count();
    for (int i = 0; i < count; i++) {
        UnknownPlayerEntry *node = unknown_players_a3fa7c[i];
        if (Compare_Wide_007837d3(node->Name, name) == 0) {
            return node;
        }
    }
    return 0;
}
