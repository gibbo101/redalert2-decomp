// DynamicVectorClass<AbstractClass *>::Resize (0x004CE160; DynamicVectorClass<AbstractClass *> vtable 0x007a177c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class AbstractClass;

template class DynamicVectorClass<AbstractClass *>;
