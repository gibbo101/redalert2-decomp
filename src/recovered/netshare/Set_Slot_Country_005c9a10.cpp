// void __fastcall Set_Slot_Country_005c9a10(HWND dialog, int id) (0x005C9A10)
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
// @ref ?Set_Value_00672a30@UnknownSessionState@@QAEXH_N@Z=00672a30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38

void __fastcall Set_Slot_Country_005c9a10(HWND dialog, int id)
{
    int country = Side_Combo_Data_4d1c70(dialog, id, -1);
    int slot = Side_Combo_Player_4d13b0(id);
    if (slot == unknown_lobby_a3fa94) {
        unknown_session_a3d298.Set_Value_00672a30(country, false);
        if (unknown_players_a3fa7c.Count() != 0) {
            unknown_players_a3fa7c[0]->unknown_66e2d0(country);
        }
    } else {
        NodeNameType *entry = unknown_player_slots_a3fa98[slot];
        if (entry != 0 && (entry == unknown_easy_ai_entry_a72d34 || entry == unknown_medium_ai_entry_a72d38
                           || entry == unknown_hard_ai_entry_a72d3c)) {
            unknown_lobby_a3d2fc[slot] = country;
        } else {
            unknown_lobby_a3d2fc[slot] = -1;
            unknown_lobby_a3d2dc[slot] = -1;
            unknown_lobby_a3d31c[slot] = -1;
        }
    }
}
