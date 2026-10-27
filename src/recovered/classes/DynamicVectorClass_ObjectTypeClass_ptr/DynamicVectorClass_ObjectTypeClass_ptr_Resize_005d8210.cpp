// DynamicVectorClass<ObjectTypeClass *>::Resize (0x005D8210; DynamicVectorClass<ObjectTypeClass *> vtable 0x007a768c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ObjectTypeClass;

template class DynamicVectorClass<ObjectTypeClass *>;
