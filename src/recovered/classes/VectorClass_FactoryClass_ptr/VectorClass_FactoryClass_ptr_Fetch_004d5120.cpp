// VectorClass<FactoryClass *>::Fetch (0x004D5120; VectorClass<FactoryClass *> vtable 0x007a2504 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class FactoryClass;

template class VectorClass<FactoryClass *>;
