// 0x0051F3F0: writes the storm and dominator state, then each list as a count and its
// anim pointers.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/com_persist.hpp"

// @ref ?StormActive@@3_NA=00a51934
// @ref ?StormCoords@@3VCell@@A=00a51878
// @ref ?StormOwner@@3PAVHouseClass@@A=00a51940
// @ref ?StormDeferment@@3HA=00a51938
// @ref ?StormTimeToEnd@@3_NA=00a51944
// @ref ?StormStartTime@@3HA=007ddb10
// @ref ?StormDuration@@3HA=007ddb14
// @ref ?unknown_dominator_start_7ddb18@@3HA=007ddb18
// @ref ?unknown_dominator_delay_7ddb1c@@3HA=007ddb1c
// @ref ?unknown_dominator_state_a5193c@@3HA=00a5193c
// @ref ?StormCloudsPresent@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51880
// @ref ?StormBoltsPresent@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a518c8
// @ref ?StormCloudsManifesting@@3V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51908

HRESULT __fastcall Save_Storm_0051F3F0(IStream *stream)
{
    HRESULT result = stream->Write(&StormActive, 1, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&StormStartTime, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&StormDuration, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&StormDeferment, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&StormTimeToEnd, 1, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&unknown_dominator_start_7ddb18, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&unknown_dominator_delay_7ddb1c, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&unknown_dominator_state_a5193c, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&StormCoords, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Write(&StormOwner, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    int count;
    count = StormCloudsManifesting.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int i = 0; i < count; i++) {
        AnimClass *anim = StormCloudsManifesting[i];
        result = stream->Write(&anim, sizeof(anim), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    count = StormCloudsPresent.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int j = 0; j < count; j++) {
        AnimClass *anim = StormCloudsPresent[j];
        result = stream->Write(&anim, sizeof(anim), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    count = StormBoltsPresent.Count();
    result = stream->Write(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int k = 0; k < count; k++) {
        AnimClass *anim = StormBoltsPresent[k];
        result = stream->Write(&anim, sizeof(anim), 0);
        if (FAILED(result)) {
            return result;
        }
    }
    return result;
}
