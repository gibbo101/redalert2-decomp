// DynamicVectorClass<ObjectTypeClass *>::ID_object (0x005D82C0; DynamicVectorClass<ObjectTypeClass *> vtable 0x007a768c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class ObjectTypeClass;

template class DynamicVectorClass<ObjectTypeClass *>;
