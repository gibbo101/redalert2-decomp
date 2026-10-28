// void Unknown_Free_Lobby_Entries_005c8950() (0x005C8950)
// Frees the seven fixed lobby entries (0x00A72D2C..0x00A72D44, zeroing each pointer)
// and every session node, then clears the node list (0x005A7480, which frees
// each element again through the list's virtual Clear).
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUUnknownPlayerEntry@@A=00a72d44
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUUnknownPlayerEntry@@A=00a72d2c
// @ref ?Free_Pointers_005a7480@@YIXPAV?$DynamicVectorClass@PAUUnknownPlayerEntry@@@@@Z=005a7480
// @ref ?Free_Memory_00781d3b@@YAXPAX@Z=00781d3b

void Unknown_Free_Lobby_Entries_005c8950()
{
    if (unknown_lobby_entries_a72d2c[0] != 0) {
        Free_Memory_00781d3b(unknown_lobby_entries_a72d2c[0]);
        unknown_lobby_entries_a72d2c[0] = 0;
    }
    if (unknown_lobby_entries_a72d2c[1] != 0) {
        Free_Memory_00781d3b(unknown_lobby_entries_a72d2c[1]);
        unknown_lobby_entries_a72d2c[1] = 0;
    }
    if (unknown_lobby_entries_a72d2c[2] != 0) {
        Free_Memory_00781d3b(unknown_lobby_entries_a72d2c[2]);
        unknown_lobby_entries_a72d2c[2] = 0;
    }
    if (unknown_lobby_entries_a72d2c[3] != 0) {
        Free_Memory_00781d3b(unknown_lobby_entries_a72d2c[3]);
        unknown_lobby_entries_a72d2c[3] = 0;
    }
    if (unknown_lobby_entries_a72d2c[4] != 0) {
        Free_Memory_00781d3b(unknown_lobby_entries_a72d2c[4]);
        unknown_lobby_entries_a72d2c[4] = 0;
    }
    if (unknown_lobby_entries_a72d2c[5] != 0) {
        Free_Memory_00781d3b(unknown_lobby_entries_a72d2c[5]);
        unknown_lobby_entries_a72d2c[5] = 0;
    }
    if (unknown_player_a72d44 != 0) {
        Free_Memory_00781d3b(unknown_player_a72d44);
        unknown_player_a72d44 = 0;
    }
    Free_Pointers_005a7480(&unknown_players_a3fa7c);
}
