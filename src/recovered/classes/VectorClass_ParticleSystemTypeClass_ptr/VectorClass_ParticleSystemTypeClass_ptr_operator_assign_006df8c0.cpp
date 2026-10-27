// VectorClass<ParticleSystemTypeClass *>::operator=(VectorClass const &) (0x006DF8C0)
// Instantiated from shared/vector_class.hpp for TechnoTypeClass::Read_INI and
// Load, which copy the particle-system lists (DamageParticleSystems,
// DestroyParticleSystems) through it.
#include "shared/techno_type.hpp"
// @ref ??2@YAPAXI@Z=00782017

// The generic body of shared/vector_class.hpp, written as an explicit
// specialization (VC6 cannot explicitly instantiate an operator).
template <>
VectorClass<ParticleSystemTypeClass *> &VectorClass<ParticleSystemTypeClass *>::operator=(VectorClass<ParticleSystemTypeClass *> const &vector)
{
    if (this != &vector) {
        Clear();
        VectorMax = vector.VectorMax;
        if (VectorMax) {
            Vector = new ParticleSystemTypeClass *[VectorMax];
            if (Vector) {
                IsAllocated = true;
                for (int index = 0; index < VectorMax; index++) {
                    Vector[index] = vector.Vector[index];
                }
            }
        } else {
            Vector = 0;
            IsAllocated = false;
        }
    }
    return *this;
}
