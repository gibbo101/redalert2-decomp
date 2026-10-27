// DynamicVectorClass<BuildingClass *>::ID_pointer (0x004D4A30; DynamicVectorClass<BuildingClass *> vtable 0x007a2364 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class BuildingClass;

template class DynamicVectorClass<BuildingClass *>;
