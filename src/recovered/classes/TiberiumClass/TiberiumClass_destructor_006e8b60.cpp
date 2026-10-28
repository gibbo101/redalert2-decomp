// TiberiumClass::~TiberiumClass() (0x006E8B60)
#include "shared/tiberium.hpp"
// @ref ??1AbstractTypeClass@@UAE@XZ=00410740
// @ref ?Detach_This_From_All@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVAbstractClass@@@@A=00ac0cb0

TiberiumClass::~TiberiumClass()
{
    Detach_This_From_All(this, true);
    unknown_objects_ac0cb0.Delete(this);
    unknown_TiberiumClass_list_00ac0b30.Delete(this);
    delete SpreadData;
    SpreadData = 0;
    delete SpreadMap;
    SpreadMap = 0;
    delete SpreadQueue;
    SpreadQueue = 0;
    if (GrowthQueue) {
        GrowthQueue->Clear();
        delete GrowthQueue;
        GrowthQueue = 0;
    }
    if (GrowthData) {
        delete GrowthData;
        GrowthData = 0;
    }
    if (GrowthMap) {
        delete GrowthMap;
        GrowthMap = 0;
    }
    GrowthCount = 0;
}
