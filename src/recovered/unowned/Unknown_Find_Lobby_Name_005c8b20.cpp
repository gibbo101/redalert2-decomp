// NodeNameType *__fastcall Unknown_Find_Lobby_Name_005c8b20(wchar_t const *name) (0x005C8B20)
// Finds the lobby buffer (the seven fixed ones, then the session nodes' names)
// whose text equals name (0x007837D3 compares wide strings, 0 when equal);
// null when there is none.
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40
// @ref ?Compare_Wide_007837d3@@YAHPBG0@Z=007837d3

NodeNameType *__fastcall Unknown_Find_Lobby_Name_005c8b20(wchar_t const *name)
{
    if (Compare_Wide_007837d3(unknown_open_entry_a72d2c->Name, name) == 0) {
        return unknown_open_entry_a72d2c;
    }
    if (Compare_Wide_007837d3(unknown_closed_entry_a72d30->Name, name) == 0) {
        return unknown_closed_entry_a72d30;
    }
    if (Compare_Wide_007837d3(unknown_easy_ai_entry_a72d34->Name, name) == 0) {
        return unknown_easy_ai_entry_a72d34;
    }
    if (Compare_Wide_007837d3(unknown_medium_ai_entry_a72d38->Name, name) == 0) {
        return unknown_medium_ai_entry_a72d38;
    }
    if (Compare_Wide_007837d3(unknown_hard_ai_entry_a72d3c->Name, name) == 0) {
        return unknown_hard_ai_entry_a72d3c;
    }
    if (Compare_Wide_007837d3(unknown_waiting_entry_a72d40->Name, name) == 0) {
        return unknown_waiting_entry_a72d40;
    }
    if (Compare_Wide_007837d3(unknown_player_a72d44->Name, name) == 0) {
        return unknown_player_a72d44;
    }
    int count = unknown_players_a3fa7c.Count();
    for (int i = 0; i < count; i++) {
        NodeNameType *node = unknown_players_a3fa7c[i];
        if (Compare_Wide_007837d3(node->Name, name) == 0) {
            return node;
        }
    }
    return 0;
}
