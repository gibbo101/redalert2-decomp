// bool ParticleSystemClass::Remove_Particle(int index) (0x0060B3E0)
// Ends the particle at an index (its slot 60) and drops it from the system.
#include "shared/particle_system.hpp"

bool ParticleSystemClass::Remove_Particle(int index)
{
    if (index < Particles.Count()) {
        Particles[index]->unknown_slot60();
        Particles.Delete(Particles[index]);
        return true;
    }
    return false;
}
