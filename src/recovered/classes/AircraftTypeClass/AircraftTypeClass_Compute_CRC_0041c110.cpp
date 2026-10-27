// void AircraftTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x0041C110)
#include "shared/aircraft_type.hpp"
// @ref ?Compute_CRC@TechnoTypeClass@@UBEXAAVWWCRCEngine@@@Z=006defd0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void AircraftTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    TechnoTypeClass::Compute_CRC(crc);
    crc(Rotors);
    crc(CustomRotor);
    crc(Landable);
    crc(AirportBound);
    crc(Fighter);
    crc((long)ArrayIndex);
}
