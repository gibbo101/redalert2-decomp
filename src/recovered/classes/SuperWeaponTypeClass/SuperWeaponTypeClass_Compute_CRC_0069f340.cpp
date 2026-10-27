// void SuperWeaponTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x0069F340)
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void SuperWeaponTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)ArrayIndex);
    crc((long)Action);
    crc((long)unknown_0xA0);
    crc((long)unknown_0xA4);
    crc((long)unknown_0xA8);
    crc((long)unknown_0xAC);
    crc(IsPowered);
    crc(DisableableFromShell);
    crc(PreClick);
    crc(PostClick);
    crc((long)PreDependent);
    crc(ShowTimer);
    crc((long)RechargeTime);
    crc((long)Type);
    crc(UseChargeDrain);
    crc(ManualControl);
}
