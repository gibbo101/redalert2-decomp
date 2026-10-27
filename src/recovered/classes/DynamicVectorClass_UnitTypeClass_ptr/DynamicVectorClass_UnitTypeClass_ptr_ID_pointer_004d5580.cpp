// DynamicVectorClass<UnitTypeClass *>::ID_pointer (0x004D5580; DynamicVectorClass<UnitTypeClass *> vtable 0x007a27e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class UnitTypeClass;

template class DynamicVectorClass<UnitTypeClass *>;
