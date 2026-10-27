// DynamicVectorClass<UnitClass *>::ID_pointer (0x004D4FE0; DynamicVectorClass<UnitClass *> vtable 0x007a23e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class UnitClass;

template class DynamicVectorClass<UnitClass *>;
