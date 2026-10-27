// DynamicVectorClass<InfantryTypeClass *>::ID_object (0x004FAC40; TypeList<InfantryTypeClass *> vtable 0x007a30f8 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class InfantryTypeClass;

template class DynamicVectorClass<InfantryTypeClass *>;
