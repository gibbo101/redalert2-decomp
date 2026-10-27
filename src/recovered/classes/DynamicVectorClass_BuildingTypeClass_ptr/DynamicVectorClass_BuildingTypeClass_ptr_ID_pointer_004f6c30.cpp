// DynamicVectorClass<BuildingTypeClass *>::ID_pointer (0x004F6C30; DynamicVectorClass<BuildingTypeClass *> vtable 0x007a2f28 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class BuildingTypeClass;

template class DynamicVectorClass<BuildingTypeClass *>;
