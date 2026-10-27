// DynamicVectorClass<AbstractTypeClass *>::ID_object (0x004DBBC0; DynamicVectorClass<AbstractTypeClass *> vtable 0x007a2a64 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class AbstractTypeClass;

template class DynamicVectorClass<AbstractTypeClass *>;
