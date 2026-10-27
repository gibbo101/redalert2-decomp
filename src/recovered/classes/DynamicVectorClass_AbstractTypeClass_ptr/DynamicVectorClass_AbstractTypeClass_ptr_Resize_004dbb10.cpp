// DynamicVectorClass<AbstractTypeClass *>::Resize (0x004DBB10; DynamicVectorClass<AbstractTypeClass *> vtable 0x007a2a64 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class AbstractTypeClass;

template class DynamicVectorClass<AbstractTypeClass *>;
