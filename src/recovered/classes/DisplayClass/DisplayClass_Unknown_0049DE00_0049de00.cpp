// void DisplayClass::Unknown_0049DE00(bool skip_buildings, bool arg2) (0x0049DE00)
// Over every techno (Technos) out of limbo (buildings left out when asked):
// the counterpart of 0x0049E000 with slots 262 and 235. The player's own
// with +0x373 set get slot 262 (0, 0, false, 0), the sight around them
// redrawn (0x0054A550 with +0x1F4 + 3) and, as gap generators, slot 235;
// allied buildings, when the rules' +0x142B allows, get slot 262 (0, arg2,
// false, 0) and the redraw; other houses' RevealToAll buildings slot 262
// (0, 0, true, player) and the redraw; other gap generators slot 235.
#include "shared/display.hpp"
#include "shared/techno.hpp"
#include "shared/techno_type.hpp"
#include "shared/house.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
// @ref ?Technos@@3V?$DynamicVectorClass@PAVTechnoClass@@@@A=00a40c20
// @ref ?Rules@@3PAVRulesClass@@A=00839848
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4
// @ref ?Unknown_004F52B0@HouseClass@@QAE_NXZ=004f52b0
// @ref ?Is_Ally@HouseClass@@QBE_NPBV1@@Z=004e5540
// @ref ?Unknown_0054A550@MapClass@@QAEXABUCoordStruct@@HHH@Z=0054a550

void DisplayClass::Unknown_0049DE00(bool skip_buildings, bool arg2)
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
                techno->unknown_slot262(0, 0, false, 0);
                CoordStruct coord = techno->Coord;
                Map.Unknown_0054A550(coord, 0, techno->unknown_1f4 + 3, 0);
                if (techno->unknown_slot32()->GapGenerator) {
                    techno->unknown_slot235();
                }
            }
        } else if (techno->Kind_Of() == 6 && Rules->unknown_142b && techno->House->Is_Ally(unknown_player_a35db4)) {
            techno->unknown_slot262(0, arg2, false, 0);
            CoordStruct coord = techno->Coord;
            Map.Unknown_0054A550(coord, 0, techno->unknown_1f4 + 3, 0);
        } else if (techno->Kind_Of() == 6 && techno->unknown_slot32()->RevealToAll && !techno->House->Unknown_004F52B0()) {
            techno->unknown_slot262(0, 0, true, unknown_player_a35db4);
            CoordStruct coord = techno->Coord;
            Map.Unknown_0054A550(coord, 0, techno->unknown_1f4 + 3, 0);
        } else if (techno->unknown_slot32()->GapGenerator) {
            techno->unknown_slot235();
        }
    }
}
