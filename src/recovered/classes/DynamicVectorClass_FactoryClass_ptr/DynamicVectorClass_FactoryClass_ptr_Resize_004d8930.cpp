// DynamicVectorClass<FactoryClass *>::Resize (0x004D8930; DynamicVectorClass<FactoryClass *> vtable 0x007a24e4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class FactoryClass;

template class DynamicVectorClass<FactoryClass *>;
