// DynamicVectorClass<InfantryClass *>::Clear (0x00453D20; DynamicVectorClass<InfantryClass *> vtable 0x0079d054 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class InfantryClass;

template class DynamicVectorClass<InfantryClass *>;
