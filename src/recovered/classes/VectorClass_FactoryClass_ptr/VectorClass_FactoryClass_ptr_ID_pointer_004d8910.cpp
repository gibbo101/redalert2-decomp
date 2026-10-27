// VectorClass<FactoryClass *>::ID_pointer (0x004D8910; VectorClass<FactoryClass *> vtable 0x007a2504 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class FactoryClass;

template class VectorClass<FactoryClass *>;
