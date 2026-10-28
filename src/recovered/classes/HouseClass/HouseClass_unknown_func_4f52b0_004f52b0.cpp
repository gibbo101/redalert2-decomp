// bool HouseClass::unknown_func_4f52b0() (0x004F52B0)
// In a multiplayer game whether this is the local player's house, otherwise whether a human
// flag is set (hypothesis).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

extern int unknown_game_mode_a3d298;        // 0x00A3D298

bool HouseClass::unknown_func_4f52b0()
{
    if (!unknown_game_mode_a3d298) {
        return unknown_134 || unknown_135;
    }
    return this == unknown_player_a35db4;
}
