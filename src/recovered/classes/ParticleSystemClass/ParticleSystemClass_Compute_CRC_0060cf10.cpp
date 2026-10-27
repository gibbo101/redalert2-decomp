// void ParticleSystemClass::Compute_CRC(WWCRCEngine &crc) const (0x0060CF10)
#include "shared/particle_system.hpp"
// @ref ?Compute_CRC@ObjectClass@@UBEXAAVWWCRCEngine@@@Z=005d4b10
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEXM@Z=00493f50

void ParticleSystemClass::Compute_CRC(WWCRCEngine &crc) const
{
    ObjectClass::Compute_CRC(crc);
    for (int index = 0; index < Particles.Count(); index++) {
        crc(Particles[index]->Fetch_ID());
    }
    if (Owner != 0) {
        crc(Owner->Fetch_ID());
    }
    if (unknown_d0 != 0) {
        crc(unknown_d0->Fetch_ID());
    }
    crc(unknown_d4);
    crc((long)Lifetime);
}
