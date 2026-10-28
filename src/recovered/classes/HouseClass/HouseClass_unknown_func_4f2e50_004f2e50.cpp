// void HouseClass::unknown_func_4f2e50() (0x004F2E50)
// HouseClass::AI for the player's house: once the +0x1F8 timer has run out
// the radar is on with the scenario's FreeRadar, or with full power and an
// active radar building on the map (+0x530 set, not being sold; outside the
// campaign or for a house the player does not control any, otherwise only one
// with +0x373) that has no +0x3FC and does not refuse (slot 111). The map's
// radar is switched when it differs. +0x5669 is cleared first.
#include "shared/techno.hpp"
#include "shared/building_type_class.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?Map@@3VMouseClass@@A=008324e0
// @ref ?Unknown_00633130@RadarClass@@QAE_NXZ=00633130
// @ref ?Unknown_00633140@RadarClass@@QAEX_N@Z=00633140

void HouseClass::unknown_func_4f2e50()
{
    unknown_5669 = false;
    if (this == unknown_player_a35db4) {
        bool radar = false;
        if (unknown_1f8 == 0) {
            if (unknown_id_source_a3d290->FreeRadar) {
                radar = true;
            } else if (Power_Fraction() >= 1.0) {
                for (int index = 0; index < Buildings.Count(); index++) {
                    BuildingClass *building = Buildings[index];
                    if (building != 0 && building->unknown_530 && building->Type->Radar && !building->unknown_76
                        && building->unknown_74
                        && ((unknown_game_mode_a3d298 == 0 && !unknown_134 && !unknown_135) || building->unknown_373
                            || unknown_game_mode_a3d298 != 0)
                        && building->Mission != 0x13 && building->MissionQueue != 0x13) {
                        if (building->unknown_3fc == 0 && !building->unknown_slot111()) {
                            radar = true;
                        }
                        break;
                    }
                }
            }
        }
        if (Map.Unknown_00633130() != radar) {
            Map.Unknown_00633140(radar);
        }
    }
}
