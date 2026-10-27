// void ParticleTypeClass::Compute_CRC(WWCRCEngine &crc) const (0x00621A10, slot 13)
#include "shared/particle_system.hpp"
// @ref ?Compute_CRC@AbstractTypeClass@@UBEXAAVWWCRCEngine@@@Z=00410960
// @ref ??RWWCRCEngine@@QAEXJ@Z=00493f30
// @ref ??RWWCRCEngine@@QAEX_N@Z=00493e80
// @ref ??RWWCRCEngine@@QAEXM@Z=00493f50
// @ref ??RWWCRCEngine@@QAEXN@Z=00493f70
// @ref ??RWWCRCEngine@@QAEXD@Z=00493df0

void ParticleTypeClass::Compute_CRC(WWCRCEngine &crc) const
{
    AbstractTypeClass::Compute_CRC(crc);
    crc((long)MaxDC);
    crc((long)MaxEC);
    crc((long)Damage);
    crc((long)StartFrame);
    crc((long)NumLoopFrames);
    crc((long)Translucency);
    crc((long)WindEffect);
    crc(Velocity);
    crc(Deacc);
    crc((long)Radius);
    crc(DeleteOnStateLimit);
    crc(EndStateAI);
    crc(StartStateAI);
    crc(StateAIAdvance);
    crc((long)Translucent25State);
    crc((long)Translucent50State);
    crc(Normalized);
    crc((long)NextParticle);
    crc((long)BehavesLike);
    crc(ColorSpeed);
}
