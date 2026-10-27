// DynamicVectorClass<ObjectClass *>::Clear (0x0040CB60; DynamicVectorClass<ObjectClass *> vtable 0x0079db7c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ObjectClass;

template class DynamicVectorClass<ObjectClass *>;
