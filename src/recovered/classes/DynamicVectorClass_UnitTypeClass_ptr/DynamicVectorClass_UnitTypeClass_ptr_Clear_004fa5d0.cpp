// DynamicVectorClass<UnitTypeClass *>::Clear (0x004FA5D0; TypeList<UnitTypeClass *> vtable 0x007a30d8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class UnitTypeClass;

template class DynamicVectorClass<UnitTypeClass *>;
