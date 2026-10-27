// DynamicVectorClass<BuildingClass *>::Resize (0x004D5CF0; DynamicVectorClass<BuildingClass *> vtable 0x007a2364 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class BuildingClass;

template class DynamicVectorClass<BuildingClass *>;
