// void __fastcall Set_Player_Map_State_005c3f00(char const *name, int state) (0x005C3F00)
#include "shared/lobby.hpp"
#include "shared/string_table.hpp"
// @ref ??_C@_0BE@EJOA@D?3?2Ra2?2netshare?4cpp?$AA@=007e6ebc
// @ref ?unknown_map_name_a3d342@@3PAGA=00a3d342
// @ref ??_C@_0BE@CBAO@GUI?3HostMapTransfer?$AA@=007e6ea8
// @ref ??_C@_0O@DPOL@GUI?3HostNoMap?$AA@=007e6b74

void __fastcall Set_Player_Map_State_005c3f00(char const *name, int state)
{
    if (name == 0) {
        name = unknown_name_a3d3a0;
    }
    if (Compare_Wide_007837d3(Unknown_006FA180(name), unknown_host_name_a3f618) == 0) {
        state = 1;
    }
    int found = -1;
    for (int i = 0; i < unknown_players_a3fa7c.Count(); i++) {
        if (Compare_Narrow_00781f20(Unknown_006FA120(unknown_players_a3fa7c[i]->Name), name) == 0) {
            found = i;
            break;
        }
    }
    if (found != -1) {
        unknown_players_a3fa7c[found]->unknown_map_state_6f = state;
        if (state == 0) {
            Unknown_005C2C80(-1, StringTable::Load_String("GUI:HostNoMap", 0, "D:\\Ra2\\netshare.cpp", 0x45B),
                             unknown_players_a3fa7c[found]->Name, unknown_map_name_a3d342);
        } else if (state == 2) {
            Unknown_005C2C80(-1, StringTable::Load_String("GUI:HostMapTransfer", 0, "D:\\Ra2\\netshare.cpp", 0x45F),
                             unknown_players_a3fa7c[found]->Name, unknown_map_name_a3d342);
        }
    }
}
