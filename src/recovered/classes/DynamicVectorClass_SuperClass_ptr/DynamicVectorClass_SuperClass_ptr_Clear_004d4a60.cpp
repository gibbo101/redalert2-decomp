// DynamicVectorClass<SuperClass *>::Clear (0x004D4A60; DynamicVectorClass<SuperClass *> vtable 0x007a2a24 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class SuperClass;

template class DynamicVectorClass<SuperClass *>;
