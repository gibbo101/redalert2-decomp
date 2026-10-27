// void InfantryClass::Compute_CRC(WWCRCEngine &crc) const (0x005088A0, slot 13)
#include "shared/infantry.hpp"
// @ref ?Compute_CRC@FootClass@@UBEXAAVWWCRCEngine@@@Z=004ca3d0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void InfantryClass::Compute_CRC(WWCRCEngine &crc) const
{
    FootClass::Compute_CRC(crc);
    crc((long)Sequence);
    crc(unknown_5b0.Value());
    crc((long)unknown_5bc);
    crc(unknown_5c1);
    crc(unknown_5c2);
    crc(unknown_5c3);
    crc(unknown_5c4);
    crc(unknown_5c5);
}
