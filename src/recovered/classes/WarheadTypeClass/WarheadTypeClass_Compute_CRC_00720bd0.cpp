// void WarheadTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00720BD0)
#include "shared/warhead_type.hpp"
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0

void WarheadTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc(Wall);
    crc(Wood);
    crc(Tiberium);
    crc(unknown_148);
    crc(Sparky);
    crc(Sonic);
    crc(Fire);
    crc(Conventional);
    crc(Rocker);
    crc(Bright);
    crc(CLDisableRed);
    crc(CLDisableGreen);
    crc(CLDisableBlue);
    crc(Deform);
    crc((long)DeformThreshhold);
    crc(ProneDamage);
    crc(Veinhole);
    crc((long)ShakeXlo);
    crc((long)ShakeXhi);
    crc((long)ShakeYlo);
    crc((long)ShakeYhi);
    for (int i = 0; i < 11; i++) {
        crc(Verses[i]);
    }
    crc((long)AnimList.Count());
    crc((long)InfDeath);
}
