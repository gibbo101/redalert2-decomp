#include "shared/particle_system.hpp"
// @ref ??_C@_06CPHF@?$DMnone?$DO?$AA@=007cdecc
int __fastcall ParticleSystemTypeClass::Index_Or_Make(char const *name)
{
    if (_stricmp(name, "<none>") != 0 && strlen(name) != 0) {
        for (int index = 0; index < ParticleSystemTypes.Count(); ++index) {
            if (_stricmp(name, ParticleSystemTypes[index]->ID) == 0) return index;
        }
        ParticleSystemTypeClass *type = new ParticleSystemTypeClass(name);
        return ParticleSystemTypes.ID(type);
    }
    return -1;
}
