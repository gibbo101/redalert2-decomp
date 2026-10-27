// ?Compute_CRC@ParasiteClass@@UBEXAAVWWCRCEngine@@@Z (0x00606460)
// AbstractClass part, the victim ID and the state.
#include "shared/parasite.hpp"
// @ref ?Compute_CRC@AbstractClass@@UBEXAAVWWCRCEngine@@@Z=004101b0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void ParasiteClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractClass::Compute_CRC(crc);
    if (Victim != 0) {
        crc(Victim->Fetch_ID());
    }
    crc((long)unknown_48);
    crc((long)unknown_4c);
    crc((long)unknown_50);
    crc(unknown_54);
}
