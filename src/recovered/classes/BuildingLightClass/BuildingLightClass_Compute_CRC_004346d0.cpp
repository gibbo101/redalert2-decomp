// void BuildingLightClass::Compute_CRC(WWCRCEngine &crc) const (0x004346D0)
#include "shared/building_light.hpp"
// @ref ?Compute_CRC@ObjectClass@@UBEXAAVWWCRCEngine@@@Z=005d4b10
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70

void BuildingLightClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectClass::Compute_CRC(crc);
    crc(unknown_98);
    crc((long)unknown_a0.X);
    crc((long)unknown_a0.Y);
    crc((long)unknown_a0.Z);
    crc((long)unknown_ac.X);
    crc((long)unknown_ac.Y);
    crc((long)unknown_ac.Z);
    crc(unknown_b8);
    crc(unknown_c0);
    crc((long)Behavior);
    if (Following != 0) {
        crc(Following->Fetch_ID());
    }
    if (Owner != 0) {
        crc(Owner->Fetch_ID());
    }
}
