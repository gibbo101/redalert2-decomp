// ParticleSystemClass range-limited trailing particle insertion, 0060B2D0.
#include "shared/particle_system.hpp"
extern "C" int __cdecl abs(int);
// @ref ??0ParticleClass@@QAE@PAVParticleTypeClass@@ABUCoordStruct@@1PAVParticleSystemClass@@@Z=00608440
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ??2@YAPAXI@Z=00782017
ParticleClass *ParticleSystemClass::Spawn_Particle(CoordStruct const &coord, CoordStruct const &target, int const range)
{
    if (Class->HoldsWhat == -1) return 0;
    ParticleClass *particle = new ParticleClass(ParticleTypes[Class->HoldsWhat], coord, target, this);
    if (particle == 0 || range <= 0) return 0;
    Particles.Add(particle);
    int count = Particles.Count();
    ParticleClass **data = &Particles[0];
    int limited_range = range;
    if (count < limited_range) limited_range = count;
    int offset = abs(unknown_id_source_a3d290->Random()()) % limited_range;
    int source = count - 2;
    int stop = count - offset - 2;
    int insert = count - offset;
    if (source > stop) {
        ParticleClass **position = data + source;
        int remaining = source - stop;
        do {
            position[1] = *position;
            --position;
        } while (--remaining != 0);
    }
    data[insert - 1] = particle;
    return particle;
}
