// DynamicVectorClass<AbstractClass *>::Clear (0x004CDE30; DynamicVectorClass<AbstractClass *> vtable 0x007a177c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class AbstractClass;

template class DynamicVectorClass<AbstractClass *>;
