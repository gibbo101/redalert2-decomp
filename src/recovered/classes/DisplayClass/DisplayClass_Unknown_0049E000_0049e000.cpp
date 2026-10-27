// void DisplayClass::Unknown_0049E000(bool skip_buildings, bool arg2) (0x0049E000)
// Over every techno (Technos) out of limbo (buildings left out when asked):
// the player's own with +0x373 set get slot 263 (0, 0, false, 0) and, as
// gap generators, slot 236; allied buildings, when the rules' +0x142B
// allows, get slot 263 (0, arg2, false, 0); other gap generators slot 236.
#include "shared/display.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

void DisplayClass::Unknown_0049E000(bool skip_buildings, bool arg2)
{
    int count = Technos.Count();
    for (int index = 0; index < count; index++) {
        TechnoClass *techno = Technos[index];
        if (techno == 0 || techno->unknown_76) {
            continue;
        }
        if (techno->Kind_Of() == 6 && skip_buildings) {
            continue;
        }
        if (techno->House->Unknown_004F52B0()) {
            if (techno->unknown_373) {
                techno->unknown_slot263(0, 0, false, 0);
                if (techno->unknown_slot32()->GapGenerator) {
                    techno->unknown_slot236();
                }
            }
        } else if (techno->Kind_Of() == 6 && Rules->unknown_142b && techno->House->Is_Ally(unknown_player_a35db4)) {
            techno->unknown_slot263(0, arg2, false, 0);
        } else if (techno->unknown_slot32()->GapGenerator) {
            techno->unknown_slot236();
        }
    }
}
