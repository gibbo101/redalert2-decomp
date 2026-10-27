// DynamicVectorClass<ObjectClass *>::ID_pointer (0x0040CB90; DynamicVectorClass<ObjectClass *> vtable 0x0079db7c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class ObjectClass;

template class DynamicVectorClass<ObjectClass *>;
