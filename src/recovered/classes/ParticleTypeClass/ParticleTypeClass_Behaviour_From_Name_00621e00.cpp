// int __fastcall ParticleTypeClass::Behaviour_From_Name(char const *name) (0x00621E00)
// The BehavesLike= index of a name, -1 when unknown.
#include "shared/particle_system.hpp"
// @ref ?unknown_particle_behaviour_names_7ec1b4@@3PAPBDA=007ec1b4

int __fastcall ParticleTypeClass::Behaviour_From_Name(char const *name)
{
    for (int index = 0; index < 5; index++) {
        if (!_stricmp(name, unknown_particle_behaviour_names_7ec1b4[index])) {
            return index;
        }
    }
    return -1;
}
