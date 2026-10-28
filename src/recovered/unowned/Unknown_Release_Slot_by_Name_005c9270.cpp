// void __fastcall Unknown_Release_Slot_by_Name_005c9270(char const *name) (0x005C9270)
// Finds the player slot whose node name (narrowed) equals name and gives it back to the
// lobby: a node with no ID (-1) becomes the seventh fixed entry, any other
// goes to the first fixed entry within the slot limit and to the second beyond it.
#include "shared/lobby.hpp"
// @ref ?unknown_player_a72d44@@3PAUNodeNameType@@A=00a72d44
// @ref ?unknown_lobby_entries_a72d2c@@3PAPAUNodeNameType@@A=00a72d2c
// @ref ?unknown_player_slots_a3fa98@@3PAPAUNodeNameType@@A=00a3fa98
// @ref ?unknown_lobby_flag_7e6d90@@3HA=007e6d90
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?unknown_73c370@@YA_NXZ=0073c370
// @ref ?unknown_73c3a0@@YA_NXZ=0073c3a0
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Compare_Narrow_00781f20@@YAHPBD0@Z=00781f20

void __fastcall Unknown_Release_Slot_by_Name_005c9270(char const *name)
{
    int limit = 4;
    if (unknown_game_mode_a3d298 == 4) {
        if (unknown_73c370() && !unknown_73c3a0()) {
            limit = 2;
        }
    } else {
        limit = 8;
    }
    if (unknown_lobby_flag_7e6d90 == 0 && limit < 7) {
        limit++;
    }
    for (int i = 0; i < 8; i++) {
        NodeNameType *node = unknown_player_slots_a3fa98[i];
        if (node != 0 && Compare_Narrow_00781f20(name, Unknown_006FA120(node->Name)) == 0) {
            if (unknown_player_slots_a3fa98[i]->Team == -1) {
                unknown_player_slots_a3fa98[i] = unknown_player_a72d44;
                return;
            }
            NodeNameType *entry = unknown_lobby_entries_a72d2c[0];
            if (i >= limit) {
                entry = unknown_lobby_entries_a72d2c[1];
            }
            unknown_player_slots_a3fa98[i] = entry;
            return;
        }
    }
}
