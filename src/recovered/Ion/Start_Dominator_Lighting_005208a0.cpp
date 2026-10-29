// 0x005208A0: the dominator lighting starts: state 1 for 30 frames, the
// scenario's +0x828 timer restarted at 1 and the dominator ambient applied.
#include "shared/lightning_storm.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
// @ref ?unknown_dominator_start_7ddb18@@3HA=007ddb18
// @ref ?unknown_dominator_delay_7ddb1c@@3HA=007ddb1c
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0

void __fastcall Start_Dominator_Lighting_005208A0()
{
    unknown_dominator_state_a5193c = 1;
    unknown_dominator_delay_7ddb1c = 30;
    unknown_dominator_start_7ddb18 = Frame;
    unknown_id_source_a3d290->unknown_828 = 1;
    unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->unknown_22e0;
    Set_Lighting_00520B00(unknown_id_source_a3d290->unknown_22e4 * 1000 / 100,
        unknown_id_source_a3d290->unknown_22e8 * 1000 / 100,
        unknown_id_source_a3d290->unknown_22ec * 1000 / 100, true);
    Map.Flag_To_Redraw(true);
}
