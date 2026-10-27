// void HouseTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x004F9E40)
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEJPBXH@Z=00493fc0
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void HouseTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)House);
    crc((long)Side);
    crc((long)Color);
    crc(FirepowerMult);
    crc(GroundspeedMult);
    crc(AirspeedMult);
    crc(ArmorMult);
    crc(ROFMult);
    crc(CostMult);
    crc(BuildtimeMult);
    crc(Suffix, strlen(Suffix));
    crc(Prefix);
    crc(Multiplay);
}
