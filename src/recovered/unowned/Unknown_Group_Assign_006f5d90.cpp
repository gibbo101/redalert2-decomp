// void __fastcall Unknown_006F5D90(int group) (0x006F5D90)
// Assigns group (group - 1 at +0x1AC) to every selected player-side techno
// of the map, after clearing it from the others that held it.
#include "shared/uicmnds.hpp"
// @ref ?unknown_game_mode_a3d298@@3HA=00a3d298
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20


void __fastcall Unknown_006F5D90(int group)
{
    int count = Technos.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = Technos[index];
        if (techno != 0 && !techno->unknown_76) {
            if (Is_Player_Side(techno)) {
                if (techno->unknown_1ac == group - 1) {
                    techno->unknown_1ac = -1;
                }
                if (techno->unknown_77) {
                    techno->unknown_1ac = group - 1;
                }
            }
        }
    }
}
