// void ParticleSystemClass::unknown_func_60b4e0() (0x0060B4E0)
// Behaviour 1 (gas): every particle runs its behaviour, then each finished
// particle is replaced by its type's next particle (carrying velocity and
// step over) and removed; the others move.
#include "shared/particle_system.hpp"
#include "shared/unknown_geometry.hpp"
// @ref ??0ParticleClass@@QAE@PAVParticleTypeClass@@ABUCoordStruct@@1PAVParticleSystemClass@@@Z=00608440
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ??2@YAPAXI@Z=00782017
// @ref ?unknown_func_609c90@ParticleClass@@QAEXXZ=00609c90
// @ref ?unknown_func_60a420@ParticleClass@@QAEXXZ=0060a420

void ParticleSystemClass::unknown_func_60b4e0()
{
    int index;
    for (index = Particles.Count() - 1; index >= 0; index--) {
        Particles[index]->unknown_func_609c90();
    }
    for (index = Particles.Count() - 1; index >= 0; index--) {
        ParticleClass *particle = Particles[index];
        if (particle->unknown_121) {
            ParticleTypeClass *type = particle->Class;
            if (type->NextParticle != -1) {
                CoordStruct position = particle->Coord;
                ParticleTypeClass *next = ParticleTypes[type->NextParticle];
                CoordStruct coord = position + type->NextParticleOffset;
                ParticleClass *spawned = new ParticleClass(next, coord, unknown_geometry_l, 0);
                if (spawned != 0) {
                    Particles.Add(spawned);
                    spawned->Velocity = particle->Velocity;
                    spawned->unknown_b0 = particle->unknown_b0;
                }
            }
            particle->unknown_slot60();
        } else {
            particle->unknown_func_60a420();
        }
    }
}
