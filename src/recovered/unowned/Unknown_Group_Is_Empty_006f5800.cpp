// bool __fastcall Unknown_006F5800(int group) (0x006F5800)
// Whether no player-side, unselected techno of the map belongs to group
// (group - 1 is stored at +0x1AC).
#include "shared/uicmnds.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20


bool __fastcall Unknown_006F5800(int group)
{
    int count = Technos.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && !techno->unknown_76) {
            if (Is_Player_Side(techno) && !techno->unknown_77 && techno->unknown_1ac == group - 1) {
                return false;
            }
        }
    }
    return true;
}
