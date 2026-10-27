// bool HouseClass::unknown_func_4f52f0() (0x004F52F0)
// In a multiplayer game the +0x134 flag, otherwise whether either of the +0x134 and +0x135 flags is set (hypothesis).
#include "shared/techno.hpp"
#include "shared/house_views.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298

extern int unknown_game_mode_a3d298;        // 0x00A3D298

bool HouseClass::unknown_func_4f52f0()
{
    if (unknown_game_mode_a3d298) {
        return unknown_134;
    }
    if (!unknown_134 && !unknown_135) {
        return false;
    }
    return true;
}
