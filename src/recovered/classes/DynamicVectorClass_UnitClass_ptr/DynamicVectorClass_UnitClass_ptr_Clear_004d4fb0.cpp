// DynamicVectorClass<UnitClass *>::Clear (0x004D4FB0; DynamicVectorClass<UnitClass *> vtable 0x007a23e4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class UnitClass;

template class DynamicVectorClass<UnitClass *>;
