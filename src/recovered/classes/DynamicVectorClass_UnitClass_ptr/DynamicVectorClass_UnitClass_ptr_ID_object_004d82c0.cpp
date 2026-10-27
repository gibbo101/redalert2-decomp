// DynamicVectorClass<UnitClass *>::ID_object (0x004D82C0; DynamicVectorClass<UnitClass *> vtable 0x007a23e4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class UnitClass;

template class DynamicVectorClass<UnitClass *>;
