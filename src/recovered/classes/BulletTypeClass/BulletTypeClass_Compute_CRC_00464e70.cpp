// void BulletTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00464E70, slot 13)
// The base CRC, then the flight flags and values (Westwood's selection).
// Extent: the inventory stops at 0x00464F52; a linear sweep reaches the ret 4
// at 0x00464F9F, followed by nop padding to the Load at 0x00464FB0.
#include "shared/bullet_type.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70

void BulletTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc(Airburst);
    crc(Shadow);
    crc(Arcing);
    crc(Dropping);
    crc(Level);
    crc(Inviso);
    crc(Proximity);
    crc(Ranged);
    crc(Rotates);
    crc(Inaccurate);
    crc(FlakScatter);
    crc(AA);
    crc(AG);
    crc(Degenerates);
    crc(Bouncy);
    crc(Elasticity);
    crc((long)Acceleration);
    crc((long)ROT);
    crc((long)Arm);
    crc(Flat);
}
