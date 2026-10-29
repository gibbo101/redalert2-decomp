// 0x00520770: reapplies the dominator or storm lighting (after a load).
#include "shared/lightning_storm.hpp"
#include "shared/id_source.hpp"
#include "shared/house.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref ?unknown_player_a35db4@@3PAVHouseClass@@A=00a35db4

void Unknown_00520770()
{
    if (unknown_dominator_state_a5193c == 1) {
        unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->unknown_22e0;
        Set_Lighting_00520B00(unknown_id_source_a3d290->unknown_22e4 * 1000 / 100,
            unknown_id_source_a3d290->unknown_22e8 * 1000 / 100,
            unknown_id_source_a3d290->unknown_22ec * 1000 / 100, true);
    } else if (StormActive) {
        unknown_player_a35db4->unknown_5669 = true;
        unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->IonAmbient;
        Set_Lighting_00520B00(unknown_id_source_a3d290->IonRed * 1000 / 100,
            unknown_id_source_a3d290->IonGreen * 1000 / 100,
            unknown_id_source_a3d290->IonBlue * 1000 / 100, true);
    }
}
