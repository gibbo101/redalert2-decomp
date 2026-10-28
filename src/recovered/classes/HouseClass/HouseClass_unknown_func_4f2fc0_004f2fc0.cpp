// void HouseClass::unknown_func_4f2fc0() (0x004F2FC0)
// HouseClass::AI for the player's house: the spy satellite view is on while
// one of its buildings is an active spy satellite on the map that is not
// being sold (mission 0x13, current or queued); outside the campaign or for a
// house the player does not control any such building counts, otherwise only
// one with +0x373. Turning it on or off plays the Rules sound and reveals or
// covers the map. +0x5669 is cleared first.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/rules.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0

void HouseClass::unknown_func_4f2fc0()
{
    unknown_5669 = false;
    if (this == unknown_player_a35db4) {
        for (int index = 0; index < Buildings.Count(); index++) {
            BuildingClass *building = Buildings[index];
            if (building != 0 && building->Type->SpySat && !building->unknown_76 && building->unknown_74
                && ((unknown_game_mode_a3d298 == 0 && !unknown_134 && !unknown_135) || building->unknown_373
                    || unknown_game_mode_a3d298 != 0)
                && building->Mission != 0x13 && building->MissionQueue != 0x13) {
                if (!unknown_566a) {
                    Voc_Play(Rules->SpySatActivationSound, 1.0f, 0x2000, 0);
                    Map.Unknown_0055A120();
                    unknown_566a = true;
                }
                return;
            }
        }
        if (unknown_566a) {
            Map.Unknown_00559F10();
            Voc_Play(Rules->SpySatDeactivationSound, 1.0f, 0x2000, 0);
            unknown_566a = false;
        }
    }
}
