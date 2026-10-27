// void UnitClass::Compute_CRC(WWCRCEngine &crc) const (0x00707DF0, slot 13)
// FootClass's CRC, then the type (kind and ID), the object at +0x5B0, and
// a few unit fields.
#include "shared/unit.hpp"
// @ref ?Compute_CRC@FootClass@@UBEXAAVWWCRCEngine@@@Z=004ca3d0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void UnitClass::Compute_CRC(WWCRCEngine &crc) const
{
    FootClass::Compute_CRC(crc);
    crc((long)Type->Kind_Of());
    crc(Type->Fetch_ID());
    if (unknown_5b0) {
        crc(unknown_5b0->Fetch_ID());
    }
    crc((long)unknown_5b4);
    crc(unknown_5b8);
    crc(unknown_5b9);
    crc(unknown_5ba);
    crc(unknown_577);
}
