// void RadioClass::Compute_CRC(WWCRCEngine &crc) const (0x00636BF0, slot 13)
// MissionClass's part, the contact count and each contact's ID and kind.
#include "shared/radio.hpp"
#include "shared/techno.hpp"
// @ref ?Compute_CRC@MissionClass@@UBEXAAVWWCRCEngine@@@Z=00595040
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void RadioClass::Compute_CRC(WWCRCEngine &crc) const
{
    MissionClass::Compute_CRC(crc);
    crc((long)RadioLinks.Length());
    for (int index = 0; index < RadioLinks.Length(); index++) {
        if (RadioLinks[index] != 0) {
            crc((long)RadioLinks[index]->Fetch_ID());
            crc((long)RadioLinks[index]->Kind_Of());
        }
    }
}
