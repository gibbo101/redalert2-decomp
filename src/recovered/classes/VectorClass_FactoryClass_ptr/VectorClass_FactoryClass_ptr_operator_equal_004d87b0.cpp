// VectorClass<FactoryClass *>::operator equal (0x004D87B0; VectorClass<FactoryClass *> vtable 0x007a2504 slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class FactoryClass;

template class VectorClass<FactoryClass *>;
