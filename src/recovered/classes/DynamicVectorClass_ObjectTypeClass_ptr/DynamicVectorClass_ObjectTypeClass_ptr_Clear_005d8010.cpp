// DynamicVectorClass<ObjectTypeClass *>::Clear (0x005D8010; DynamicVectorClass<ObjectTypeClass *> vtable 0x007a768c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class ObjectTypeClass;

template class DynamicVectorClass<ObjectTypeClass *>;
