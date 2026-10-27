// DynamicVectorClass<ObjectClass *>::ID_object (0x0040CDF0; DynamicVectorClass<ObjectClass *> vtable 0x0079db7c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class ObjectClass;

template class DynamicVectorClass<ObjectClass *>;
