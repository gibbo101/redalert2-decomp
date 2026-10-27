// DynamicVectorClass<UnitTypeClass *>::ID_object (0x004DA660; DynamicVectorClass<UnitTypeClass *> vtable 0x007a27e4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class UnitTypeClass;

template class DynamicVectorClass<UnitTypeClass *>;
