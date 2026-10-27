// int __fastcall Unknown_006F7DF0(TechnoClass *techno) (0x006F7DF0)
// Whether a player-side techno in play is not a building (kind 6).
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
#include "shared/uicmnds.hpp"


int __fastcall Unknown_006F7DF0(TechnoClass *techno)
{
    if (techno != 0 && techno->unknown_7d) {
        if (Is_Player_Side(techno)) {
            if (techno->Kind_Of() != 6) {
                return 1;
            }
        }
    }
    return 0;
}
