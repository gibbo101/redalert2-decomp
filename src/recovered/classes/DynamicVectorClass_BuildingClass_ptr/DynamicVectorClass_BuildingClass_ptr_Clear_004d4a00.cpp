// DynamicVectorClass<BuildingClass *>::Clear (0x004D4A00; DynamicVectorClass<BuildingClass *> vtable 0x007a2364 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class BuildingClass;

template class DynamicVectorClass<BuildingClass *>;
