// VectorClass<FactoryClass *>::Clear (0x004D88A0; VectorClass<FactoryClass *> vtable 0x007a2504 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class FactoryClass;

template class VectorClass<FactoryClass *>;
