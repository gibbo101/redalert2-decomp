// DynamicVectorClass<ObjectTypeClass *>::ID_pointer (0x005D8040; DynamicVectorClass<ObjectTypeClass *> vtable 0x007a768c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class ObjectTypeClass;

template class DynamicVectorClass<ObjectTypeClass *>;
