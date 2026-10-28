// void Unknown_Pregame_Setup_005c74f0() (0x005C74F0)
// Starts a multiplayer game's pregame state: the scenario takes the session's
// tech level, the frame counter and the crate count are reset, the number of
// players is logged and the global game options take the session's bridge and
// harvester settings with tiberium growing and spreading.
#include "shared/unknown_globals.hpp"
#include "shared/id_source.hpp"
#include "shared/cd_timer.hpp"
#include "shared/special.hpp"
#include "shared/lobby.hpp"
// @ref ?unknown_session_a3d2b4@@3HA=00a3d2b4
// @ref ?unknown_session_a3d2c8@@3HA=00a3d2c8
// @ref ?unknown_session_a3d2ac@@3HA=00a3d2ac
// @ref ?unknown_session_a3d33d@@3_NA=00a3d33d
// @ref ?unknown_a40b18@@3HA=00a40b18
// @ref ??_C@_0BP@KEDC@Pregame?5setup?5for?5?$CFd?5players?4?6?$AA@=007e70f8
// @ref ?Debug_Log@@YAXPBDZZ=004068f0
// @ref ?unknown_special_a40920@@3VSpecialClass@@A=00a40920
// @ref ?Unknown_0068B410@SpecialClass@@QAEXXZ=0068b410

void Debug_Log(char const *format, ...);

void Unknown_Pregame_Setup_005c74f0()
{
    unknown_id_source_a3d290->TechLevel = unknown_session_a3d2b4;
    Frame = 0;
    unknown_session_a3d55c = unknown_players_a3fa7c.Count();
    Debug_Log("Pregame setup for %d players.\n", unknown_players_a3fa7c.Count());
    unknown_a40b18 = unknown_session_a3d2c8;
    unknown_session_a3d2ac = 2;
    unknown_special_a40920.DestroyableBridges = unknown_session_a3d2c0;
    unknown_special_a40920.HarvesterImmune = unknown_session_a3d33d;
    unknown_special_a40920.TiberiumGrows = true;
    unknown_special_a40920.TiberiumSpreads = true;
    unknown_special_a40920.Unknown_0068B410();
}
