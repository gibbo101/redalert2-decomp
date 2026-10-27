// DynamicVectorClass<SuperClass *>::Resize (0x004D5F50; DynamicVectorClass<SuperClass *> vtable 0x007a2a24 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class SuperClass;

template class DynamicVectorClass<SuperClass *>;
