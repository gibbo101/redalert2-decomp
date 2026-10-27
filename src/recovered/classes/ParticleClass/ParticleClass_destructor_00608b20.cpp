// ParticleClass::~ParticleClass() (0x00608B20)
// Leaves the map (ObjectClass slot 52, qualified), then the particle list.
#include "shared/particle.hpp"
// @ref ?unknown_slot52@ObjectClass@@UAE_NXZ=005d3700
// @ref ?Unknown_006ECB90@@YIXPAVAbstractClass@@_N@Z=006ecb90
// @ref ??1ObjectClass@@UAE@XZ=005d2530

ParticleClass::~ParticleClass()
{
    ObjectClass::unknown_slot52();
    Unknown_006ECB90(this, true);
    Class = 0;
    unknown_ParticleClass_list_00a35e28.Delete(this);
}
