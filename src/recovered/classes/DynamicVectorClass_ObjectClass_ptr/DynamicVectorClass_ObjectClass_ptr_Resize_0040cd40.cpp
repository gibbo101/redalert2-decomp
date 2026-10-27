// DynamicVectorClass<ObjectClass *>::Resize (0x0040CD40; DynamicVectorClass<ObjectClass *> vtable 0x0079db7c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class ObjectClass;

template class DynamicVectorClass<ObjectClass *>;
