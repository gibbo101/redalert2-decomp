// void TerrainTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x006E58C0)
// Note: the base called is AbstractTypeClass's (0x00410960).
#include "shared/terrain_type.hpp"
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXM@Z=00493f50

void TerrainTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)ArrayIndex);
    crc(WaterBound);
    crc(SpawnsTiberium);
    crc(IsFlammable);
    crc((long)Foundation);
    crc(IsAnimated);
    crc((long)AnimationRate);
    crc(AnimationProbability);
}
