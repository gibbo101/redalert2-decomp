// DynamicVectorClass<AbstractTypeClass *>::ID_pointer (0x004D58E0; DynamicVectorClass<AbstractTypeClass *> vtable 0x007a2a64 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class AbstractTypeClass;

template class DynamicVectorClass<AbstractTypeClass *>;
