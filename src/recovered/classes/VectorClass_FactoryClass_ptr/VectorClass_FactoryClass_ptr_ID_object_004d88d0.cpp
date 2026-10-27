// VectorClass<FactoryClass *>::ID_object (0x004D88D0; VectorClass<FactoryClass *> vtable 0x007a2504 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class FactoryClass;

template class VectorClass<FactoryClass *>;
