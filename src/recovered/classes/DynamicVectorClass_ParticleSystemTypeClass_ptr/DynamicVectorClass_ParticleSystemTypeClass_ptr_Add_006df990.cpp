// DynamicVectorClass<ParticleSystemTypeClass *>::Add(ParticleSystemTypeClass * const &object) (0x006DF990)
// Instantiated from shared/vector_class.hpp for TechnoTypeClass::Read_INI
// and Load, which append to the particle-system lists through it.
#include "shared/techno_type.hpp"

// The generic body of shared/vector_class.hpp, written as an explicit
// specialization (VC6 emits no code for an explicit member instantiation).
template <>
bool DynamicVectorClass<ParticleSystemTypeClass *>::Add(ParticleSystemTypeClass * const &object)
{
    if (ActiveCount >= Length()) {
        if ((IsAllocated || !VectorMax) && GrowthStep > 0) {
            if (!Resize(Length() + GrowthStep)) {
                return false;
            }
        } else {
            return false;
        }
    }
    int index = ActiveCount++;
    Vector[index] = object;
    return true;
}
