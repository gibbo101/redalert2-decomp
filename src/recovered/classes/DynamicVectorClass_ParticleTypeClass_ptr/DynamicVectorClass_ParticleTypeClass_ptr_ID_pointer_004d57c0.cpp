// DynamicVectorClass<ParticleTypeClass *>::ID_pointer (0x004D57C0; DynamicVectorClass<ParticleTypeClass *> vtable 0x007a2964 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class ParticleTypeClass;

template class DynamicVectorClass<ParticleTypeClass *>;
