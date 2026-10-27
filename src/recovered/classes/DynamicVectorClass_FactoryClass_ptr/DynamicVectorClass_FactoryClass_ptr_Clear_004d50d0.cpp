// DynamicVectorClass<FactoryClass *>::Clear (0x004D50D0; DynamicVectorClass<FactoryClass *> vtable 0x007a24e4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class FactoryClass;

template class DynamicVectorClass<FactoryClass *>;
