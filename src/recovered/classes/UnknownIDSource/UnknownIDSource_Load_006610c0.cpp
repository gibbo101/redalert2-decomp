// void UnknownIDSource::Load(IStream *stream) (0x006610C0)
// Reads the scenario back from a saved game (called after Clear_Scenario by
// the game load 0x00656B85): stops the elapsed time, reads the whole object
// and rebuilds it in place, reads the three allowable-unit lists, asks for
// the unit type pointers to be fixed up, fetches the mission timer text again
// and restarts the elapsed time.
// @ref ??_C@_0CD@GJLD@Scenario?5Load?3?5ElapsedTimer?5?$DN?5?$CFl@=007f236c
// @ref ??0UnknownIDSource@@QAE@ABVNoInitClass@@@Z=0065b780
// @ref ??0?$DynamicVectorClass@PAVTechnoTypeClass@@@@QAE@IPBQAVTechnoTypeClass@@@Z=006634e0
// @ref ?Add@?$DynamicVectorClass@PAVTechnoTypeClass@@@@QAE_NABQAVTechnoTypeClass@@@Z=00663540
// @ref ??0?$DynamicVectorClass@H@@QAE@IPBH@Z=0046d1f0
// @ref ?Add@?$DynamicVectorClass@H@@QAE_NABH@Z=0046d300
// @ref ??_C@_0BE@DADK@D?3?2Ra2?2Scenario?4CPP?$AA@=007f1df0
#include "shared/id_source.hpp"
#include "shared/type_list.hpp"
#include "shared/abstract.hpp"
#include "shared/string_table.hpp"
#include "shared/abstract_type.hpp"
#include "shared/debug_printf.hpp"

void UnknownIDSource::Load(IStream *stream)
{
    ElapsedTime.Stop();
    stream->Read(this, sizeof(*this), 0);
    new (this) UnknownIDSource(NoInitClass());
    AllowableUnits.Load(stream);
    AllowableUnitMaximums.Load(stream);
    AllowableUnitCounts.Load(stream);
    for (int index = 0; index < AllowableUnits.Count(); index++) {
        Swizzle_Pointer(AllowableUnits[index]);
    }
    if (MissionTimerLabel[0] != 0) {
        MissionTimerText = StringTable::Load_String(MissionTimerLabel, 0, "D:\\Ra2\\Scenario.CPP", 6379);
    } else {
        MissionTimerText = unknown_empty_wide_839d4c;
    }
    ElapsedTime.Start();
    Debug_Printf("Scenario Load: ElapsedTimer = %ld\n", ElapsedTime);
}
