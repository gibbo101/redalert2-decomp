// char const *__fastcall ParticleSystemTypeClass::Name_From(unsigned int index) (0x00620C40)
// The ID of the indexed type, "<none>" when the index is out of range.
#include "shared/particle_system.hpp"
// @ref ?ParticleSystemTypes@@3V?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@A=00a35dd0
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc

char const *__fastcall ParticleSystemTypeClass::Name_From(unsigned int index)
{
    if (index < (unsigned int)ParticleSystemTypes.Count()) {
        return ParticleSystemTypes[index]->ID;
    }
    return "<none>";
}
