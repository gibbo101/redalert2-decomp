// bool __fastcall Unknown_Is_Color_Taken_005c95d0(int color) (0x005C95D0)
// True when a player slot holds a real player (not empty and not one of the fixed
// lobby entries) whose colour (0x0066E2A0) is color, or when color is already one
// of the eight per-slot values of 0x00A3D31C. -2 (random) is never taken.
// Set_Slot_Color_005c9ab0 inlines it (with the entry test as an inline helper).
#include "shared/lobby.hpp"
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_lobby_a3d31c@@3PAHA=00a3d31c
// @ref ?unknown_66e2a0@NodeNameType@@QAEHXZ=0066e2a0

static bool Is_Player_Entry(NodeNameType *entry)
{
    return entry != 0 && entry != unknown_open_entry_a72d2c && entry != unknown_closed_entry_a72d30 &&
        entry != unknown_waiting_entry_a72d40 && entry != unknown_player_a72d44;
}

bool __fastcall Unknown_Is_Color_Taken_005c95d0(int color)
{
    if (color != -2) {
        int i;
        for (i = 0; i < 8; i++) {
            NodeNameType *entry = unknown_player_slots_a3fa98[i];
            if (Is_Player_Entry(entry) &&
                entry != unknown_easy_ai_entry_a72d34 && entry != unknown_medium_ai_entry_a72d38 &&
                entry != unknown_hard_ai_entry_a72d3c && entry->unknown_66e2a0() == color) {
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
