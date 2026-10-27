// char const *__fastcall ParticleTypeClass::Name_From(unsigned int index) (0x006219F0)
// The ID of the indexed particle type, 0 when the index is out of range.
#include "shared/particle_system.hpp"
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00

char const *__fastcall ParticleTypeClass::Name_From(unsigned int index)
{
    if (index < (unsigned int)ParticleTypes.Count()) {
        return ParticleTypes[index]->ID;
    }
    return 0;
}
