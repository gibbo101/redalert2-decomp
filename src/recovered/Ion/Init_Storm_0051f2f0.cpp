// 0x0051F2F0: resets the storm and dominator state, empties the cloud and
// bolt lists and returns the scenario's ambient light.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/id_source.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ?StormActive@@3_NA=00a51934
// @ref ?StormCoords@@3VCell@@A=00a51878
// @ref ?StormOwner@@3PAVHouseClass@@A=00a51940
// @ref ?StormDeferment@@3HA=00a51938
// @ref ?StormStartTime@@3HA=007ddb10
// @ref ?StormDuration@@3HA=007ddb14
// @ref ?unknown_dominator_start_7ddb18@@3HA=007ddb18
// @ref ?unknown_dominator_delay_7ddb1c@@3HA=007ddb1c
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?CloudsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51880
// @ref ?BoltsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a518c8
// @ref ?CloudsManifesting@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51908
// @ref ?Set_Lighting_00520B00@@YIXHHH_N@Z=00520b00
// @ref _unknown_geometry_k=00a518a8
// @ref ??3@YAXPAX@Z=00781d3b

void __fastcall Init_Storm_0051F2F0()
{
    StormCoords = unknown_geometry_k;
    StormActive = false;
    unknown_dominator_state_a5193c = 0;
    StormStartTime = -1;
    StormDuration = -1;
    unknown_dominator_start_7ddb18 = -1;
    unknown_dominator_delay_7ddb1c = -1;
    StormDeferment = 0;
    StormOwner = 0;
    IonStormClass::CloudsManifesting.Clear();
    IonStormClass::CloudsPresent.Clear();
    IonStormClass::BoltsPresent.Clear();
    unknown_id_source_a3d290->unknown_22b0 = unknown_id_source_a3d290->unknown_22a8;
    Set_Lighting_00520B00(-1, -1, -1, false);
}
