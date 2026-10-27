#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_OBJECT
#define VECTOR_IMPLEMENT_DYNAMIC_DELETE_INDEX
#include "shared/particle_system.hpp"
// @ref ?ParticleSystemTypes@@3V?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@A=00a35dd0
ParticleSystemTypeClass::~ParticleSystemTypeClass()
{
    Unknown_006ECB90(this, true);
    ParticleSystemTypes.Delete(this);
}
