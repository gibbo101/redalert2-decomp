// ParticleClass *ParticleSystemClass::Spawn_Held_Particle(ParticleTypeClass *type, CoordStruct const &coord) (0x0060B240)
// A particle of a given type at a coordinate (no target, no system), added
// to the system.
#include "shared/particle_system.hpp"

ParticleClass *ParticleSystemClass::Spawn_Held_Particle(ParticleTypeClass *type, CoordStruct const &coord)
{
    ParticleClass *particle = new ParticleClass(type, coord, unknown_geometry_l, 0);
    if (particle != 0) {
        Particles.Add(particle);
        return particle;
    }
    return 0;
}
