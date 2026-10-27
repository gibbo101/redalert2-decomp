// DynamicVectorClass<BuildingClass *>::ID_object (0x004D5DA0; DynamicVectorClass<BuildingClass *> vtable 0x007a2364 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class BuildingClass;

template class DynamicVectorClass<BuildingClass *>;
