// SpawnManagerClass::~SpawnManagerClass() (0x00689A80)
// Kills the spawned units unless the game is shutting down, frees the
// records and leaves the unit's list.
#include "shared/spawn_manager.hpp"
#include "shared/unknown_globals.hpp"
// @ref ??_7SpawnManagerClass@@6BIPersistStream@@@=007ab8c8
// @ref ??_7SpawnManagerClass@@6BIRTTITypeInfo@@@=007ab8ac
// @ref ??_7SpawnManagerClass@@6BINoticeSink@@@=007ab8a4
// @ref ??_7SpawnManagerClass@@6BINoticeSource@@@=007ab89c
// @ref ??_7?$VectorClass@PAUSpawnControl@@@@6B@=007ab94c
// @ref ??3@YAXPAX@Z=00781d3b
// @ref ??1AbstractClass@@UAE@XZ=0040ff90
// @ref ?unknown_flag_a40958@@3_NA=00a40958
// @ref ?Kill_Nodes@SpawnManagerClass@@QAEXXZ=00689b70
// @ref ?unknown_SpawnManagerClass_list_00abd028@@3V?$DynamicVectorClass@PAVSpawnManagerClass@@@@A=00abd028

SpawnManagerClass::~SpawnManagerClass()
{
    if (unknown_flag_a40958) {
        Kill_Nodes();
    }
    for (int i = SpawnedNodes.Count() - 1; i >= 0; i--) {
        delete SpawnedNodes[i];
    }
    DynamicVectorClass<SpawnControl *> &nodes = SpawnedNodes;
    int length = nodes.Length();
    nodes.Clear();
    nodes.Resize(length);
    unknown_SpawnManagerClass_list_00abd028.Delete(this);
}
