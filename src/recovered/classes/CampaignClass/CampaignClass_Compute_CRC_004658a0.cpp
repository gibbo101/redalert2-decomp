// ?Compute_CRC@CampaignClass@@UBEXAAVWWCRCEngine@@@Z (0x004658A0)
// AbstractTypeClass part and the campaign fields.
#include "shared/campaign.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXPBD@Z=00493f90

void CampaignClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)unknown_98);
    crc(Scenario);
    crc((long)unknown_29c);
}
