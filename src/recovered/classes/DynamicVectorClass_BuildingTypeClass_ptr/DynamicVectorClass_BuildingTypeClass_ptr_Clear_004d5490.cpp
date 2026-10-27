// DynamicVectorClass<BuildingTypeClass *>::Clear (0x004D5490; DynamicVectorClass<BuildingTypeClass *> vtable 0x007a2764 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class BuildingTypeClass;

template class DynamicVectorClass<BuildingTypeClass *>;
