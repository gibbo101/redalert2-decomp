// int __fastcall ParticleSystemTypeClass::Behaviour_From_Name(char const *name) (0x00620DB0)
// The BehavesLike= index of a name, -1 when unknown.
#include "shared/particle_system.hpp"
// @ref ?unknown_behaviour_names_7ebfd8@@3PAPBDA=007ebfd8

int __fastcall ParticleSystemTypeClass::Behaviour_From_Name(char const *name)
{
    for (int index = 0; index < 5; index++) {
        if (!_stricmp(name, unknown_behaviour_names_7ebfd8[index])) {
            return index;
        }
    }
    return -1;
}
