// void Unknown_Free_Lobby_Entries_005c8950() (0x005C8950)
// Frees the seven fixed lobby entries (0x00A72D2C..0x00A72D44, zeroing each pointer)
// and every session node, then clears the node list (0x005A7480, which frees
// each element again through the list's virtual Clear).
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40
// @ref ?Free_Pointers_005a7480@@YIXPAV?$DynamicVectorClass@PAUNodeNameType@@@@@Z=005a7480
// @ref ?Free_Memory_00781d3b@@YAXPAX@Z=00781d3b

void Unknown_Free_Lobby_Entries_005c8950()
{
    if (unknown_open_entry_a72d2c != 0) {
        Free_Memory_00781d3b(unknown_open_entry_a72d2c);
        unknown_open_entry_a72d2c = 0;
    }
    if (unknown_closed_entry_a72d30 != 0) {
        Free_Memory_00781d3b(unknown_closed_entry_a72d30);
        unknown_closed_entry_a72d30 = 0;
    }
    if (unknown_easy_ai_entry_a72d34 != 0) {
        Free_Memory_00781d3b(unknown_easy_ai_entry_a72d34);
        unknown_easy_ai_entry_a72d34 = 0;
    }
    if (unknown_medium_ai_entry_a72d38 != 0) {
        Free_Memory_00781d3b(unknown_medium_ai_entry_a72d38);
        unknown_medium_ai_entry_a72d38 = 0;
    }
    if (unknown_hard_ai_entry_a72d3c != 0) {
        Free_Memory_00781d3b(unknown_hard_ai_entry_a72d3c);
        unknown_hard_ai_entry_a72d3c = 0;
    }
    if (unknown_waiting_entry_a72d40 != 0) {
        Free_Memory_00781d3b(unknown_waiting_entry_a72d40);
        unknown_waiting_entry_a72d40 = 0;
    }
    if (unknown_player_a72d44 != 0) {
        Free_Memory_00781d3b(unknown_player_a72d44);
        unknown_player_a72d44 = 0;
    }
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
}
