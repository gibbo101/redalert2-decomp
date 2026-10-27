// void ParticleSystemTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00620C60, slot 13)
#include "shared/particle_system.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXM@Z=00493f50

void ParticleSystemTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)HoldsWhat);
    crc(Spawns);
    crc((long)SpawnFrames);
    crc(Slowdown);
    crc((long)ParticleCap);
    crc((long)SpawnRadius);
    crc(SpawnCutoff);
    crc(SpawnTranslucencyCutoff);
    crc((long)BehavesLike);
    crc((long)Lifetime);
}
