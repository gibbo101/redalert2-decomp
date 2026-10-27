// DynamicVectorClass<SideClass *>::Clear (0x004D5190; DynamicVectorClass<SideClass *> vtable 0x007a2564 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class SideClass;

template class DynamicVectorClass<SideClass *>;
