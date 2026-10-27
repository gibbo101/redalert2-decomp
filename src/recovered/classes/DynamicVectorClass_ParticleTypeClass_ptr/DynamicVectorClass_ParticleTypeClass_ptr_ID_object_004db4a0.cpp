// DynamicVectorClass<ParticleTypeClass *>::ID_object (0x004DB4A0; DynamicVectorClass<ParticleTypeClass *> vtable 0x007a2964 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class ParticleTypeClass;

template class DynamicVectorClass<ParticleTypeClass *>;
