// DynamicVectorClass<InfantryTypeClass *>::Clear (0x004D5610; DynamicVectorClass<InfantryTypeClass *> vtable 0x007a2864 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class InfantryTypeClass;

template class DynamicVectorClass<InfantryTypeClass *>;
