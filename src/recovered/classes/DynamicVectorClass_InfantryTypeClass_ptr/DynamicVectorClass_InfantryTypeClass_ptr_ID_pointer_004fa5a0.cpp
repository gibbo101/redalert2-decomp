// DynamicVectorClass<InfantryTypeClass *>::ID_pointer (0x004FA5A0; TypeList<InfantryTypeClass *> vtable 0x007a30f8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class InfantryTypeClass;

template class DynamicVectorClass<InfantryTypeClass *>;
