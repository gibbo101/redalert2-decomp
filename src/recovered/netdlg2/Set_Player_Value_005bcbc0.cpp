// void __fastcall Set_Player_Value_005bcbc0(char const *name, int value) (0x005BCBC0)
#include "shared/lobby.hpp"
// @ref ?Unknown_005bbdd0@@YIX_N@Z=005bbdd0

void __fastcall Set_Player_Value_005bcbc0(char const *name, int value)
{
    if (name == 0) {
        name = unknown_name_a3d3a0;
        if (value == 0) {
            HWND dialog = Find_Dialog_00735940(0xBD);
            Unknown_005cd030(dialog, true);
        }
    }
    if (Compare_Wide_007837d3(Unknown_006FA180(name), unknown_host_name_a3f618) == 0) {
        value = 1;
    }
    int found = -1;
    for (int i = 0; i < unknown_players_a3fa7c.Count(); i++) {
        if (Compare_Narrow_00781f20(Unknown_006FA120(unknown_players_a3fa7c[i]->Name), name) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        unknown_players_a3fa7c[found]->unknown_67 = value;
    }
    Unknown_005bbdd0(false);
}
