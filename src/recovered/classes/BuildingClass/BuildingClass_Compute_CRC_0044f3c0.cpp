// void BuildingClass::Compute_CRC(WWCRCEngine &crc) const (0x0044F3C0, slot 13)
// The techno CRC, then the timers' remaining time, the plain members, the
// owned and target objects' IDs and the flags.
#include "shared/building.hpp"
// @ref ?Compute_CRC@TechnoClass@@UBEXAAVWWCRCEngine@@@Z=006d6aa0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0

void BuildingClass::Compute_CRC(WWCRCEngine &crc) const
{
    TechnoClass::Compute_CRC(crc);
    crc(unknown_420.Value());
    crc(unknown_5a0.Value());
    crc((long)unknown_42c);
    crc((long)unknown_430);
    crc((long)unknown_434);
    if (unknown_438 != 0) {
        crc(unknown_438->Fetch_ID());
    }
    crc((long)unknown_43c);
    if (unknown_440 != 0) {
        crc(unknown_440->Fetch_ID());
    }
    crc(unknown_448.Value());
    crc((long)unknown_4d0);
    crc((long)unknown_4ec);
    crc((long)unknown_4f0);
    crc(unknown_530);
    crc(unknown_5ba);
    crc(unknown_59a);
    crc(unknown_59b);
    crc(unknown_5ac);
    crc(unknown_5ad);
    crc(unknown_5b8);
    crc(unknown_5ae);
    crc(unknown_5af);
    crc(unknown_5b0);
    crc(unknown_5b1);
    crc(unknown_5b2);
    crc(unknown_5b3);
    crc(unknown_5b4);
    crc(unknown_59c);
    crc(unknown_5b5);
    crc(unknown_5b6);
    crc((long)(unsigned short)unknown_5c4);
    crc(unknown_5c6);
}
