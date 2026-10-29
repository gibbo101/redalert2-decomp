// int __fastcall Unknown_006F6FE0(TechnoClass *techno, int argument) (0x006F6FE0)
// Whether a techno (in play, +0x7D) belongs to the player's side: its house
// flag +0x135 in a single-player game, else the house's slot 0x004F52B0 answer.
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
#include "shared/uicmnds.hpp"


int __fastcall Unknown_006F6FE0(TechnoClass *techno, int argument)
{
    if (techno != 0 && techno->unknown_7d) {
        bool mine;
        if (unknown_game_mode_a3d298 == 0) {
            mine = techno->House->unknown_135;
        } else {
            mine = techno->House->Unknown_004F52B0();
        }
        if (mine) {
            return 1;
        }
    }
    return 0;
}
