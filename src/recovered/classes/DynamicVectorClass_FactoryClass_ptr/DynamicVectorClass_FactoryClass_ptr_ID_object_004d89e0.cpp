// DynamicVectorClass<FactoryClass *>::ID_object (0x004D89E0; DynamicVectorClass<FactoryClass *> vtable 0x007a24e4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class FactoryClass;

template class DynamicVectorClass<FactoryClass *>;
