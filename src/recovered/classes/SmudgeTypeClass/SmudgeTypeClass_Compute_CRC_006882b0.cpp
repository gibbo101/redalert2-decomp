// void SmudgeTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x006882B0)
// Note: the base called is AbstractTypeClass's (0x00410960), not
// ObjectTypeClass's.
#include "shared/smudge_type.hpp"
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80

void SmudgeTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)ArrayIndex);
    crc(Crater);
    crc(Burn);
    crc((long)Width);
    crc((long)Height);
}
