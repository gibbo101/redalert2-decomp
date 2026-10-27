// DynamicVectorClass<InfantryClass *>::Resize (0x004542B0; DynamicVectorClass<InfantryClass *> vtable 0x0079d054 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class InfantryClass;

template class DynamicVectorClass<InfantryClass *>;
