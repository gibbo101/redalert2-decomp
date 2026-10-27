// DynamicVectorClass<SuperClass *>::ID_pointer (0x004D4A90; DynamicVectorClass<SuperClass *> vtable 0x007a2a24 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class SuperClass;

template class DynamicVectorClass<SuperClass *>;
