// SpawnManagerClass::SpawnManagerClass() (0x00689910)
// The class factory's empty manager.
#include "shared/spawn_manager.hpp"
// @ref ??_7SpawnManagerClass@@6BIPersistStream@@@=007ab8c8
// @ref ??_7SpawnManagerClass@@6BIRTTITypeInfo@@@=007ab8ac
// @ref ??_7SpawnManagerClass@@6BINoticeSink@@@=007ab8a4
// @ref ??_7SpawnManagerClass@@6BINoticeSource@@@=007ab89c
// @ref ??0AbstractClass@@QAE@XZ=0040ff10
// @ref ??0?$VectorClass@PAUSpawnControl@@@@QAE@IPBQAUSpawnControl@@@Z=0068b0e0
// @ref ??_7?$DynamicVectorClass@PAUSpawnControl@@@@6B@=007ab92c
// @ref ?Frame@@3HA=00a40d2c
// @ref ?unknown_SpawnManagerClass_list_00abd028@@3V?$DynamicVectorClass@PAVSpawnManagerClass@@@@A=00abd028

SpawnManagerClass::SpawnManagerClass()
{
    Owner = 0;
    SpawnType = 0;
    SpawnCount = 0;
    unknown_50 = 0;
    Destination = 0;
    Target = 0;
    Status = 0;
    unknown_5c = 0;
    unknown_SpawnManagerClass_list_00abd028.Add(this);
}
