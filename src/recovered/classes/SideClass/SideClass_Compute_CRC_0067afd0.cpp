// void SideClass::Compute_CRC(WWCRCEngine &crc) const (0x0067AFD0)
// The AbstractTypeClass data and the number of houses.
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30

void SideClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)Houses.Count());
}
