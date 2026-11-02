// void DisplayClass::Unknown_0049E110(bool skip_buildings, bool arg2) (0x0049E110)
// Over the technos of layer 2 (buildings left out when asked): the player's
// own with +0x373 set get slot 70 (false, arg2); allied buildings, when the
// rules' +0x142B allows, get slot 70 (arg2, 0).
#include "shared/display.hpp"
#include "shared/techno.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
// @ref ?Layer@DisplayClass@@2PAVLayerClass@@A=00852578
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540

void DisplayClass::Unknown_0049E110(bool skip_buildings, bool arg2)
{
    for (int index = 0; index < Layer[2].Count(); index++) {
        TechnoClass *techno = (TechnoClass *)Layer[2][index];
        if (techno == 0 || !techno->AbstractFlags.IsTechno) {
            continue;
        }
        if (techno->Kind_Of() == 6 && skip_buildings) {
            continue;
        }
        if (techno->House->Unknown_004F52B0()) {
            if (techno->unknown_373) {
                techno->unknown_slot70(false, arg2);
            }
        } else if (techno->Kind_Of() == 6 && Rules->unknown_142b && techno->House->Is_Ally(unknown_player_a35db4)) {
            techno->unknown_slot70(arg2, 0);
        }
    }
}
