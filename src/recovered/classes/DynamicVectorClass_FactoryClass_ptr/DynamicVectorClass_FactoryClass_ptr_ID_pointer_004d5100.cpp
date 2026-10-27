// DynamicVectorClass<FactoryClass *>::ID_pointer (0x004D5100; DynamicVectorClass<FactoryClass *> vtable 0x007a24e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class FactoryClass;

template class DynamicVectorClass<FactoryClass *>;
