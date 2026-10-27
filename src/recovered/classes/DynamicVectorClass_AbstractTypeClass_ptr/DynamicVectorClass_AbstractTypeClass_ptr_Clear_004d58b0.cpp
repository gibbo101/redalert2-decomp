// DynamicVectorClass<AbstractTypeClass *>::Clear (0x004D58B0; DynamicVectorClass<AbstractTypeClass *> vtable 0x007a2a64 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class AbstractTypeClass;

template class DynamicVectorClass<AbstractTypeClass *>;
