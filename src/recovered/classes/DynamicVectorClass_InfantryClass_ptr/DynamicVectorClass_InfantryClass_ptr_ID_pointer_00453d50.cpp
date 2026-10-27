// DynamicVectorClass<InfantryClass *>::ID_pointer (0x00453D50; DynamicVectorClass<InfantryClass *> vtable 0x0079d054 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class InfantryClass;

template class DynamicVectorClass<InfantryClass *>;
