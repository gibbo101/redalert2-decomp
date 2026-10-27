// DynamicVectorClass<ParticleClass *>::Clear (0x004D4B80; DynamicVectorClass<ParticleClass *> vtable 0x007a22a4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ParticleClass;

template class DynamicVectorClass<ParticleClass *>;
