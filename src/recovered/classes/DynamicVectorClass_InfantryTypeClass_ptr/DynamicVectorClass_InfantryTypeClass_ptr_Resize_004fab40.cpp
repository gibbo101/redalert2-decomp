// DynamicVectorClass<InfantryTypeClass *>::Resize (0x004FAB40; TypeList<InfantryTypeClass *> vtable 0x007a30f8 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class InfantryTypeClass;

template class DynamicVectorClass<InfantryTypeClass *>;
