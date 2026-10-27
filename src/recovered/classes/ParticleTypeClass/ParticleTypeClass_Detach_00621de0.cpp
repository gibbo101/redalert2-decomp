// void ParticleTypeClass::Detach(AbstractClass *target, bool all) (0x00621DE0, slot 10)
// Forgets the warhead when it is the target.
#include "shared/particle_system.hpp"

void ParticleTypeClass::Detach(AbstractClass *target, bool all)
{
    if (Warhead == target) {
        Warhead = 0;
    }
}
