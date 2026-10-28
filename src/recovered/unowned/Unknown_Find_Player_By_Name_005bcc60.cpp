// int __fastcall Unknown_Find_Player_By_Name_005bcc60(char const *name) (0x005BCC60)
// Looks a nick name up: no name means the local one (0x00A3D3A0); the host's name (0x00A3F618) answers 1;
// otherwise the last session player whose name matches (case-insensitively) answers its +0x67 field, -1 when none does.
#include "shared/lobby.hpp"
// @ref ?unknown_name_a3d3a0@@3PADA=00a3d3a0
// @ref ?unknown_host_name_a3f618@@3PAGA=00a3f618
// @ref ?Unknown_006FA180@@YIPAGPBD@Z=006fa180
// @ref ?Unknown_006FA120@@YIPADPBG@Z=006fa120
// @ref ?Compare_Wide_007837d3@@YAHPBG0@Z=007837d3
// @ref ?Compare_Narrow_00781f20@@YAHPBD0@Z=00781f20

int __fastcall Unknown_Find_Player_By_Name_005bcc60(char const *name)
{
    if (name == 0) {
        name = unknown_name_a3d3a0;
    }
    if (Compare_Wide_007837d3(Unknown_006FA180(name), unknown_host_name_a3f618) == 0) {
        return 1;
    }
    int found = -1;
    for (int i = 0; i < unknown_players_a3fa7c.Count(); i++) {
        if (Compare_Narrow_00781f20(Unknown_006FA120(unknown_players_a3fa7c[i]->Name), name) == 0) {
            found = i;
        }
    }
    if (found != -1) {
        return unknown_players_a3fa7c[found]->unknown_67;
    }
    return -1;
}
