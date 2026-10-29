// void __fastcall Set_Slot_Color_005c9ab0(HWND dialog, int id) (0x005C9AB0)
#include "shared/lobby.hpp"
#include "shared/gdlg_supp.hpp"
// @ref ?Set_Value_00672ae0@UnknownSessionState@@QAEXH_N@Z=00672ae0
// @ref ?unknown_66e300@NodeNameType@@QAEXH@Z=0066e300
// @ref ?unknown_closed_entry_a72d30@@3PAUNodeNameType@@A=00a72d30
// @ref ?unknown_easy_ai_entry_a72d34@@3PAUNodeNameType@@A=00a72d34
// @ref ?unknown_hard_ai_entry_a72d3c@@3PAUNodeNameType@@A=00a72d3c
// @ref ?unknown_medium_ai_entry_a72d38@@3PAUNodeNameType@@A=00a72d38
// @ref ?unknown_open_entry_a72d2c@@3PAUNodeNameType@@A=00a72d2c
// @ref ?unknown_waiting_entry_a72d40@@3PAUNodeNameType@@A=00a72d40

void __fastcall Set_Slot_Color_005c9ab0(HWND dialog, int id)
{
    int color = Color_Combo_Data_4d2900(dialog, id, -1);
    int slot = Color_Combo_Player_4d1d10(id);
    if (slot == unknown_lobby_a3fa94) {
        Color_Combo_Changed_4d2700(dialog, id);
        if (Unknown_Is_Color_Taken_005c95d0(color)) {
            color = -2;
        }
        unknown_session_a3d298.Set_Value_00672ae0(color, false);
        if (unknown_players_a3fa7c.Count() != 0) {
            unknown_players_a3fa7c[0]->unknown_66e300(color);
        }
    } else {
        unknown_lobby_a3d31c[slot] = color;
    }
}
