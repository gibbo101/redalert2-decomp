// void ParticleSystemClass::Detach(AbstractClass *target, bool all) (0x0060CCA0)
// Drops a removed object: a particle, the type, unknown_d0 or the owner
// (losing the owner ends the system).
#include "shared/particle_system.hpp"
// @ref ?Detach@ObjectClass@@UAEXPAVAbstractClass@@_N@Z=005d3bd0

void ParticleSystemClass::Detach(AbstractClass *target, bool all)
{
    ObjectClass::Detach(target, all);
    Particles.Delete((ParticleClass *)target);
    if (target == Class) {
        Class = 0;
    }
    if (target == unknown_d0) {
        unknown_d0 = 0;
    }
    if (target == Owner) {
        unknown_e4 = true;
        Owner = 0;
    }
}
