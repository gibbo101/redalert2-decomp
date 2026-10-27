// DynamicVectorClass<BuildingTypeClass *>::Resize (0x004F7190; DynamicVectorClass<BuildingTypeClass *> vtable 0x007a2f28 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class BuildingTypeClass;

template class DynamicVectorClass<BuildingTypeClass *>;
