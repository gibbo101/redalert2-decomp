// DynamicVectorClass<ParticleTypeClass *>::Resize (0x004DB3F0; DynamicVectorClass<ParticleTypeClass *> vtable 0x007a2964 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ParticleTypeClass;

template class DynamicVectorClass<ParticleTypeClass *>;
