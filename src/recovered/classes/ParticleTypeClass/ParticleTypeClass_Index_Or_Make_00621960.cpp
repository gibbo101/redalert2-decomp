// int __fastcall ParticleTypeClass::Index_Or_Make(char const *name) (0x00621960)
// The index of the named particle type, made (and so appended) when
// missing; -1 for "<none>".
#include "shared/particle_system.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
// @ref ??0ParticleTypeClass@@QAE@PBD@Z=00621120
// @ref ?ParticleTypes@@3V?$DynamicVectorClass@PAVParticleTypeClass@@@@A=00a35e00
// @ref ??2@YAPAXI@Z=00782017
// @ref __stricmp=00781f20


int __fastcall ParticleTypeClass::Index_Or_Make(char const *name)
{
    if (_stricmp(name, "<none>") != 0) {
        for (int index = 0; index < ParticleTypes.Count(); index++) {
            if (_stricmp(name, ParticleTypes[index]->ID) == 0) {
                return index;
            }
        }
        ParticleTypeClass *type = new ParticleTypeClass(name);
        return ParticleTypes.ID(type);
    }
    return -1;
}
