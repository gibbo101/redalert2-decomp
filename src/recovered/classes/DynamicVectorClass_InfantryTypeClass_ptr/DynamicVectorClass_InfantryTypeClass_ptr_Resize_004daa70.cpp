// DynamicVectorClass<InfantryTypeClass *>::Resize (0x004DAA70; DynamicVectorClass<InfantryTypeClass *> vtable 0x007a2864 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class InfantryTypeClass;

template class DynamicVectorClass<InfantryTypeClass *>;
