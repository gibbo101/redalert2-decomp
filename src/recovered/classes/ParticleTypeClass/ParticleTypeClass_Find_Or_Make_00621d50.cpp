// ParticleTypeClass *__fastcall ParticleTypeClass::Find_Or_Make(char const *name) (0x00621D50)
// The named particle type, created when missing; 0 for "<none>" and "none".
#include "shared/particle_system.hpp"
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ??0ParticleTypeClass@@QAE@PBD@Z=00621120
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??_C@_04KIKH@none?$AA@=007ce0ec

ParticleTypeClass *__fastcall ParticleTypeClass::Find_Or_Make(char const *name)
{
    if (!_stricmp("<none>", name) || !_stricmp("none", name)) {
        return 0;
    }
    for (int index = 0; index < ParticleTypes.Count(); index++) {
        if (!_stricmp(ParticleTypes[index]->ID, name)) {
            return ParticleTypes[index];
        }
    }
    return new ParticleTypeClass(name);
}
