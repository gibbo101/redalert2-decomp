// DynamicVectorClass<SuperClass *>::ID_object (0x004D6000; DynamicVectorClass<SuperClass *> vtable 0x007a2a24 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class SuperClass;

template class DynamicVectorClass<SuperClass *>;
