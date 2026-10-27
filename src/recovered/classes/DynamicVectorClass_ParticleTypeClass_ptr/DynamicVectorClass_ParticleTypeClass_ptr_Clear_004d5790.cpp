// DynamicVectorClass<ParticleTypeClass *>::Clear (0x004D5790; DynamicVectorClass<ParticleTypeClass *> vtable 0x007a2964 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ParticleTypeClass;

template class DynamicVectorClass<ParticleTypeClass *>;
