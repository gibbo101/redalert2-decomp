// ParticleSystemClass::~ParticleSystemClass() (0x0060AE80)
// Deletes its particles (also removing them from the 0x00AC0CD8 list) and
// leaves the system and object lists.
#include "shared/particle_system.hpp"
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ?unknown_slot52@ObjectClass@@UAE_NXZ=005d3700
// @ref ?unknown_objects_ac0cd8@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0cd8
// @ref ?unknown_objects_ac0cb0@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0cb0
// @ref ??_7?$VectorClass@PAVParticleClass@@@@6B@=007a22c4
// @ref ??1ObjectClass@@UAE@XZ=005d2530
// @ref ??3@YAXPAX@Z=00781d3b

ParticleSystemClass::~ParticleSystemClass()
{
    Unknown_006ECB90(this, true);
    ObjectClass::unknown_slot52();
    while (Particles.Count() != 0) {
        delete Particles[0];
        unknown_objects_ac0cd8.Delete(Particles[0]);
        Particles.Delete(Particles[0]);
    }
    Class = 0;
    ParticleSystems.Delete(this);
    unknown_objects_ac0cb0.Delete(this);
    unknown_objects_ac0d60.Delete(this);
}
