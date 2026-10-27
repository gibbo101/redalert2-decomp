// VectorClass<FactoryClass *>::Resize (0x004D87F0; VectorClass<FactoryClass *> vtable 0x007a2504 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class FactoryClass;

template class VectorClass<FactoryClass *>;
