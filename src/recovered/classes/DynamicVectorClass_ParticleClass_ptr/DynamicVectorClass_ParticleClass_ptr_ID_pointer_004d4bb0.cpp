// DynamicVectorClass<ParticleClass *>::ID_pointer (0x004D4BB0; DynamicVectorClass<ParticleClass *> vtable 0x007a22a4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class ParticleClass;

template class DynamicVectorClass<ParticleClass *>;
