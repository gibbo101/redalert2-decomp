// 0x0051F5E0: reads what 0x0051F3F0 wrote; the owner and the anim pointers are
// registered for swizzling.
#define VECTOR_IMPLEMENT_ALL
#include "shared/vector_class.hpp"
#include "shared/lightning_storm.hpp"
#include "shared/com_persist.hpp"
#include "shared/swizzle.hpp"
// @ref ?Swizzle@SwizzleManagerClass@@UAGJPAPAX@Z=0069fb20
// @ref ?SwizzleManager@@3VSwizzleManagerClass@@A=00abd868
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
// @ref ?CloudsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51880
// @ref ?BoltsPresent@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a518c8
// @ref ?CloudsManifesting@IonStormClass@@2V?$DynamicVectorClass@PAVAnimClass@@@@A=00a51908

HRESULT __fastcall Load_Storm_0051F5E0(IStream *stream)
{
    HRESULT result = stream->Read(&StormActive, 1, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&StormStartTime, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&StormDuration, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&StormDeferment, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&StormTimeToEnd, 1, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&unknown_dominator_start_7ddb18, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&unknown_dominator_delay_7ddb1c, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&unknown_dominator_state_a5193c, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&StormCoords, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    result = stream->Read(&StormOwner, 4, 0);
    if (FAILED(result)) {
        return result;
    }
    SwizzleManager.Swizzle((void **)&StormOwner);
    int count;
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int i = 0; i < count; i++) {
        AnimClass *anim;
        result = stream->Read(&anim, sizeof(anim), 0);
        if (FAILED(result)) {
            return result;
        }
        IonStormClass::CloudsManifesting.Add(anim);
    }
    for (i = 0; i < count; i++) {
        SwizzleManager.Swizzle((void **)&IonStormClass::CloudsManifesting[i]);
    }
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int j = 0; j < count; j++) {
        AnimClass *anim;
        result = stream->Read(&anim, sizeof(anim), 0);
        if (FAILED(result)) {
            return result;
        }
        IonStormClass::CloudsPresent.Add(anim);
    }
    for (j = 0; j < count; j++) {
        SwizzleManager.Swizzle((void **)&IonStormClass::CloudsPresent[j]);
    }
    result = stream->Read(&count, sizeof(count), 0);
    if (FAILED(result)) {
        return result;
    }
    for (int k = 0; k < count; k++) {
        AnimClass *anim;
        result = stream->Read(&anim, sizeof(anim), 0);
        if (FAILED(result)) {
            return result;
        }
        IonStormClass::BoltsPresent.Add(anim);
    }
    for (k = 0; k < count; k++) {
        SwizzleManager.Swizzle((void **)&IonStormClass::BoltsPresent[k]);
    }
    return result;
}
