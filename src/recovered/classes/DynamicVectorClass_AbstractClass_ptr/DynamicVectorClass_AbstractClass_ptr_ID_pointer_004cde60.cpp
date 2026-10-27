// DynamicVectorClass<AbstractClass *>::ID_pointer (0x004CDE60; DynamicVectorClass<AbstractClass *> vtable 0x007a177c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AbstractClass;

template class DynamicVectorClass<AbstractClass *>;
