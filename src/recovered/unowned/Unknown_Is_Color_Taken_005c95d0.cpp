// bool __fastcall Unknown_Is_Color_Taken_005c95d0(int color) (0x005C95D0)
// True when a player slot holds a real player (not empty and not one of the fixed
// lobby entries) whose colour (0x0066E2A0) is color, or when color is already one
// of the eight per-slot values of 0x00A3D31C. -2 (random) is never taken.
#include "shared/lobby.hpp"
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUUnknownPlayerEntry@@A=00a72d2c
// @ref ?unknown_player_a72d44@@3PAUUnknownPlayerEntry@@A=00a72d44
// @ref ?unknown_player_slots_a3fa98@@3PAPAUUnknownPlayerEntry@@A=00a3fa98
// @ref ?unknown_lobby_a3d31c@@3PAHA=00a3d31c
// @ref ?unknown_66e2a0@UnknownPlayerEntry@@QAEHXZ=0066e2a0

bool __fastcall Unknown_Is_Color_Taken_005c95d0(int color)
{
    if (color != -2) {
        int i;
        for (i = 0; i < 8; i++) {
            UnknownPlayerEntry *entry = unknown_player_slots_a3fa98[i];
            if (entry != 0 && entry != unknown_lobby_entries_a72d2c[0] && entry != unknown_lobby_entries_a72d2c[1] &&
                entry != unknown_lobby_entries_a72d2c[5] && entry != unknown_player_a72d44 &&
                entry != unknown_lobby_entries_a72d2c[2] && entry != unknown_lobby_entries_a72d2c[3] &&
                entry != unknown_lobby_entries_a72d2c[4] && entry->unknown_66e2a0() == color) {
                return true;
            }
        }
        for (i = 0; i < 8; i++) {
            if (unknown_lobby_a3d31c[i] == color) {
                return true;
            }
        }
    }
    return false;
}
