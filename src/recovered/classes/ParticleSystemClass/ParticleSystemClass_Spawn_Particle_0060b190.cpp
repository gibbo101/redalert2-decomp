// ParticleClass *ParticleSystemClass::Spawn_Particle(CoordStruct const &coord, CoordStruct const &target) (0x0060B190)
// A particle of the type the system holds, added to the system.
#include "shared/particle_system.hpp"
// @ref ??0ParticleClass@@QAE@PAVParticleTypeClass@@ABUCoordStruct@@1PAVParticleSystemClass@@@Z=00608440
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ??2@YAPAXI@Z=00782017

ParticleClass *ParticleSystemClass::Spawn_Particle(CoordStruct const &coord, CoordStruct const &target)
{
    if (Class->HoldsWhat == -1) {
        return 0;
    }
    ParticleClass *particle = new ParticleClass(ParticleTypes[Class->HoldsWhat], coord, target, this);
    if (particle != 0) {
        Particles.Add(particle);
        return particle;
    }
    return 0;
}
