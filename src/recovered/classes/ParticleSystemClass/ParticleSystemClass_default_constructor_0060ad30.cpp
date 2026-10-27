// ParticleSystemClass::ParticleSystemClass() (0x0060AD30)
// An empty system registered in the system list and the 0x00AC0D60 object
// list.
#include "shared/particle_system.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ??_7?$DynamicVectorClass@PAVParticleClass@@@@6B@=007a22a4
// @ref ?ParticleSystems@@3V?$DynamicVectorClass@PAVParticleSystemClass@@@@A=00a32280
// @ref ?unknown_objects_ac0d60@@3V?$DynamicVectorClass@PAVObjectClass@@@@A=00ac0d60
// @ref ??_7ParticleSystemClass@@6BIPersistStream@@@=007a7f8c
// @ref ??_7ParticleSystemClass@@6BIRTTITypeInfo@@@=007a7f70
// @ref ??_7ParticleSystemClass@@6BINoticeSink@@@=007a7f68
// @ref ??_7ParticleSystemClass@@6BINoticeSource@@@=007a7f60

ParticleSystemClass::ParticleSystemClass() :
    Class(0),
    TargetCoord(unknown_geometry_l),
    Owner(0),
    unknown_d0(0),
    unknown_d4(0),
    Lifetime(0),
    unknown_dc(0),
    unknown_e0(0),
    unknown_e4(false),
    unknown_e5(false)
{
    Particles.Clear();
    ParticleSystems.Add(this);
    unknown_objects_ac0d60.Add(this);
}
