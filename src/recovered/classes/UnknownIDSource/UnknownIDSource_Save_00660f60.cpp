// void UnknownIDSource::Save(IStream *stream) (0x00660F60)
// Writes the scenario to a saved game (called by the game save 0x006558B0):
// the whole object, then the three allowable-unit lists, with the elapsed
// time stopped while it is written and restarted afterwards.
// @ref ??_C@_0CD@FIJM@Scenario?5Save?3?5ElapsedTimer?5?$DN?5?$CFl@=007f2348
#include "shared/id_source.hpp"
#include "shared/type_list.hpp"
#include "shared/debug_printf.hpp"

void UnknownIDSource::Save(IStream *stream)
{
    Debug_Printf("Scenario Save: ElapsedTimer = %ld\n", ElapsedTime);
    bool stopped = ElapsedTime.Started == -1;
    if (!stopped) {
        ElapsedTime.Stop();
    }
    stream->Write(this, sizeof(*this), 0);
    AllowableUnits.Save(stream);
    AllowableUnitMaximums.Save(stream);
    AllowableUnitCounts.Save(stream);
    if (!stopped) {
        ElapsedTime.Start();
    }
}
