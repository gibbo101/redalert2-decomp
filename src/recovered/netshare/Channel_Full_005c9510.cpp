// bool Channel_Full_005c9510() (0x005C9510)
#include "shared/lobby.hpp"
#include "shared/multiplayer_game_mode.hpp"
#include "shared/debug_printf.hpp"
// @ref ??_C@_0DA@HLLH@Channel?5full?5?9?5Session?4ScenarioM@=007e72f8
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_max_players_a3d558@@3HA=00a3d558
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

bool Channel_Full_005c9510()
{
    int limit = unknown_max_players_a3d558 < unknown_int_a3db1c ? unknown_max_players_a3d558 : unknown_int_a3db1c;
    if (unknown_players_a3fa7c.Count() - Unknown_005c94b0() > limit) {
        Debug_Printf("Channel full - Session.ScenarioMaxPlayers = %d\n", unknown_int_a3db1c);
        return true;
    }
    return false;
}
