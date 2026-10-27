// void WeaponTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00733AB0)
#include "shared/weapon_type.hpp"
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0

void WeaponTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)unknown_98);
    crc(unknown_10c);
    crc(unknown_11d);
    crc(unknown_11e);
    crc(unknown_11f);
    crc(unknown_121);
    crc(unknown_123);
    crc((long)Burst);
    if (Projectile != 0) {
        crc(Projectile->Fetch_ID());
    }
    crc((long)unknown_a4);
    crc((long)unknown_a8);
    if (Warhead != 0) {
        crc(Warhead->Fetch_ID());
    }
    crc((long)unknown_b0);
    crc((long)unknown_b4);
    crc((long)unknown_bc.Count());
    crc((long)Anim.Count());
    crc(unknown_105);
    crc(unknown_10a);
    crc((char)unknown_124);
    crc(unknown_122);
    crc(unknown_109);
    crc(unknown_120);
    crc(unknown_10b);
    crc(unknown_106);
    crc(unknown_107);
    crc(unknown_108);
}
