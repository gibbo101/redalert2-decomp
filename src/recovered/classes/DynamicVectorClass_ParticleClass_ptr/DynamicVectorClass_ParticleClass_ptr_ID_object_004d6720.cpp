// DynamicVectorClass<ParticleClass *>::ID_object (0x004D6720; DynamicVectorClass<ParticleClass *> vtable 0x007a22a4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class ParticleClass;

template class DynamicVectorClass<ParticleClass *>;
