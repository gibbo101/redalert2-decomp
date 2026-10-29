// 0x0051FBD0: ends an active storm: the cell and owner are cleared and,
// unless the dominator lighting holds, the scenario's ambient light returns.
#include "shared/lightning_storm.hpp"
#include "shared/id_source.hpp"
#include "shared/map_view.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?StormCoords@@3VCell@@A=00a51878
// @ref ?StormOwner@@3PAVHouseClass@@A=00a51940
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref _unknown_geometry_k=00a518a8
// @ref ?Flag_To_Redraw@GScreenClass@@UAEXH@Z=004e09a0

void __fastcall Stop_Storm_0051FBD0()
{
    if (StormActive) {
        StormActive = false;
        StormCoords = unknown_geometry_k;
        StormOwner = 0;
        if (unknown_dominator_state_a5193c != 1) {
            unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->unknown_22a8;
            Set_Lighting_00520B00(-1, -1, -1, false);
            Map.Flag_To_Redraw(true);
        }
    }
}
