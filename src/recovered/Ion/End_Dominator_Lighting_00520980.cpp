// 0x00520980: the dominator lighting ends: state 2 for 15 frames, then the
// storm's or the scenario's ambient light again.
#include "shared/lightning_storm.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?unknown_dominator_start_7ddb18@@3HA=007ddb18
// @ref ?unknown_dominator_delay_7ddb1c@@3HA=007ddb1c
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0

void __fastcall End_Dominator_Lighting_00520980()
{
    unknown_dominator_state_a5193c = 2;
    unknown_dominator_start_7ddb18 = Frame;
    unknown_dominator_delay_7ddb1c = 15;
    if (StormActive) {
        unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->IonAmbient;
        Set_Lighting_00520B00(unknown_id_source_a3d290->IonRed * 1000 / 100,
            unknown_id_source_a3d290->IonGreen * 1000 / 100,
            unknown_id_source_a3d290->IonBlue * 1000 / 100, true);
    } else {
        unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->unknown_22a8;
        Set_Lighting_00520B00(-1, -1, -1, false);
    }
    Map.Flag_To_Redraw(true);
}
