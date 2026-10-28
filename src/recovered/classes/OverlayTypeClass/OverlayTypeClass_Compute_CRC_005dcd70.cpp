// void OverlayTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x005DCD70)
// Note: the base called is AbstractTypeClass's (0x00410960).
#include "shared/overlay_type.hpp"
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void OverlayTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)ArrayIndex);
    crc((long)Land);
    crc((long)DamageLevels);
    crc((long)Strength);
    crc(Wall);
    crc(Tiberium);
    crc(Crate);
    crc(CrateTrigger);
    crc(Explodes);
}
