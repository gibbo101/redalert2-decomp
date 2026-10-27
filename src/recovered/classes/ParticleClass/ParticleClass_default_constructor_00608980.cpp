// ParticleClass::ParticleClass() (0x00608980)
// An empty particle registered in the particle list.
#include "shared/particle.hpp"
// @ref ??0ObjectClass@@QAE@XZ=005d22e0
// @ref ?unknown_ParticleClass_list_00a35e28@@3V?$DynamicVectorClass@PAVParticleClass@@@@A=00a35e28
// @ref ??_7ParticleClass@@6BIPersistStream@@@=007a7d5c
// @ref ??_7ParticleClass@@6BIRTTITypeInfo@@@=007a7d40
// @ref ??_7ParticleClass@@6BINoticeSink@@@=007a7d38
// @ref ??_7ParticleClass@@6BINoticeSource@@@=007a7d30

ParticleClass::ParticleClass() :
    Class(0),
    unknown_b0(0, 0, 0),
    unknown_bc(0),
    unknown_c0(0),
    unknown_c4(-1.0f),
    unknown_c8(0),
    unknown_cc(0),
    unknown_d0(0),
    Velocity(0),
    unknown_d8(unknown_geometry_l),
    unknown_e4(unknown_geometry_l),
    unknown_f0(unknown_geometry_l),
    unknown_fc(0, 0, 0),
    unknown_108(0, 0, 0),
    System(0),
    unknown_11c(0),
    unknown_11d(0),
    unknown_11e(0),
    unknown_11f(0),
    unknown_120(false),
    unknown_121(false)
{
    unknown_ParticleClass_list_00a35e28.Add(this);
}

// @ref _unknown_geometry_l=00a764e8
