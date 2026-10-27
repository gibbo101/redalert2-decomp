// bool ParticleSystemClass::unknown_slot17() const (0x0060CC70)
// True once the system has ended and has no particles left.
#include "shared/particle_system.hpp"

bool ParticleSystemClass::unknown_slot17() const
{
    return unknown_e4 && Particles.Count() == 0;
}
