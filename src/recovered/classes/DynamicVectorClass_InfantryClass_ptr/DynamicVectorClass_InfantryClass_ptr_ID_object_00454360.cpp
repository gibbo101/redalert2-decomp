// DynamicVectorClass<InfantryClass *>::ID_object (0x00454360; DynamicVectorClass<InfantryClass *> vtable 0x0079d054 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class InfantryClass;

template class DynamicVectorClass<InfantryClass *>;
