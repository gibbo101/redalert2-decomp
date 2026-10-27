// DynamicVectorClass<SideClass *>::ID_object (0x004D8EA0; DynamicVectorClass<SideClass *> vtable 0x007a2564 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class SideClass;

template class DynamicVectorClass<SideClass *>;
