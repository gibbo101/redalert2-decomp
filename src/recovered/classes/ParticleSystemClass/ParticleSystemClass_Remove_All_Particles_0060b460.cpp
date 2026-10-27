// void ParticleSystemClass::Remove_All_Particles() (0x0060B460)
// Remove_Particle for every particle, last first.
#include "shared/particle_system.hpp"

void ParticleSystemClass::Remove_All_Particles()
{
    for (int index = Particles.Count() - 1; index >= 0; index--) {
        Remove_Particle(index);
    }
}
