// DynamicVectorClass<ParticleClass *>::Resize (0x004D6670; DynamicVectorClass<ParticleClass *> vtable 0x007a22a4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ParticleClass;

template class DynamicVectorClass<ParticleClass *>;
