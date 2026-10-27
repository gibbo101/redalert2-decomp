// int __fastcall Unknown_006F7190(TechnoClass *techno, char const *name) (0x006F7190)
// Whether a player-side techno in play has the type name (0x005D27D0).
// @ref ?unknown_func_5d27d0@ObjectClass@@QBE_NPBD@Z=005d27d0
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
#include "shared/uicmnds.hpp"


int __fastcall Unknown_006F7190(TechnoClass *techno, char const *name)
{
    if (techno != 0 && techno->unknown_7d) {
        if (Is_Player_Side(techno)) {
            if (techno->unknown_func_5d27d0(name)) {
                return 1;
            }
        }
    }
    return 0;
}
