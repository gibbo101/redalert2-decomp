// DynamicVectorClass<InfantryTypeClass *>::Clear (0x004FA570; TypeList<InfantryTypeClass *> vtable 0x007a30f8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class InfantryTypeClass;

template class DynamicVectorClass<InfantryTypeClass *>;
