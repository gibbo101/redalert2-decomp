// void AircraftClass::Compute_CRC(WWCRCEngine &crc) const (0x0041AD60, slot 13)
#include "shared/aircraft.hpp"
// @ref ?Compute_CRC@FootClass@@UBEXAAVWWCRCEngine@@@Z=004ca3d0
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void AircraftClass::Compute_CRC(WWCRCEngine &crc) const
{
    FootClass::Compute_CRC(crc);
    crc(unknown_5b1);
    crc(unknown_5b8);
    crc(unknown_5b9);
    crc((long)unknown_5bb);
}
