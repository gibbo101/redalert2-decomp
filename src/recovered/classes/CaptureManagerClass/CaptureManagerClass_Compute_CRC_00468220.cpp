// ?Compute_CRC@CaptureManagerClass@@UBEXAAVWWCRCEngine@@@Z (0x00468220)
// AbstractClass part, then the IDs of the three objects.
#include "shared/capture_manager.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void CaptureManagerClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    if (unknown_24 != 0) {
        crc(unknown_24->Fetch_ID());
    }
    if (unknown_28 != 0) {
        crc(unknown_28->Fetch_ID());
    }
    if (Owner != 0) {
        crc(Owner->Fetch_ID());
    }
}
