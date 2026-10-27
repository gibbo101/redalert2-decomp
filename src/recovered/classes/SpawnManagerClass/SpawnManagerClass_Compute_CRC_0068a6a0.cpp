// ?Compute_CRC@SpawnManagerClass@@UBEXAAVWWCRCEngine@@@Z (0x0068A6A0)
// AbstractClass part, state, linked object IDs and timer values.
#include "shared/spawn_manager.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ?Frame@@3HA=00a40d2c

void SpawnManagerClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    crc((long)Status);
    if (Target != 0) {
        crc(Target->Fetch_ID());
    }
    if (Destination != 0) {
        crc(Destination->Fetch_ID());
    }
    crc(unknown_5c.Value());
    crc(unknown_50.Value());
    crc((long)SpawnedNodes.Count());
    crc((long)SpawnCount);
    if (SpawnType != 0) {
        crc(SpawnType->Fetch_ID());
    }
    if (Owner != 0) {
        crc(Owner->Fetch_ID());
    }
}
