// DynamicVectorClass<UnitTypeClass *>::Resize (0x004FAF10; TypeList<UnitTypeClass *> vtable 0x007a30d8 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class UnitTypeClass;

template class DynamicVectorClass<UnitTypeClass *>;
