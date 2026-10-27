// DynamicVectorClass<SideClass *>::Resize (0x004D8DF0; DynamicVectorClass<SideClass *> vtable 0x007a2564 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class SideClass;

template class DynamicVectorClass<SideClass *>;
