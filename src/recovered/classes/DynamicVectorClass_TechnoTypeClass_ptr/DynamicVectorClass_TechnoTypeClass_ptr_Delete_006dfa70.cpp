// DynamicVectorClass<TechnoTypeClass *>::Delete(int index) (0x006DFA70)
// Instantiated from shared/vector_class.hpp by TechnoTypeClass's destructor,
// whose TechnoTypes.Delete(this) expands Delete(T const &) and calls this.
#include "shared/techno_type.hpp"

// The generic body of shared/vector_class.hpp, written as an explicit
// specialization (VC6 emits no code for an explicit member instantiation).
template <>
bool DynamicVectorClass<TechnoTypeClass *>::Delete(int index)
{
    if (index < ActiveCount) {
        ActiveCount--;
        for (int i = index; i < ActiveCount; i++) {
            Vector[i] = Vector[i + 1];
        }
        return true;
    }
    return false;
}
