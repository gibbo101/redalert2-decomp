// ParticleSystemTypeClass *__fastcall ParticleSystemTypeClass::Find_Or_Make(char const *name) (0x00620DF0)
// The named type, created when missing; 0 for "<none>" and "none".
#include "shared/particle_system.hpp"
// @ref ?ParticleSystemTypes@@3V?$DynamicVectorClass@PAVParticleSystemTypeClass@@@@A=00a35dd0
// @ref ??0ParticleSystemTypeClass@@QAE@PBD@Z=00620600
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

ParticleSystemTypeClass *__fastcall ParticleSystemTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name) || !_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < ParticleSystemTypes.Count(); index++) {
        if (!_stricmp(ParticleSystemTypes[index]->ID, name)) {
            return ParticleSystemTypes[index];
        }
    }
    return new ParticleSystemTypeClass(name);
}
