// DynamicVectorClass<TerrainTypeClass *>::Clear (0x004D5430; DynamicVectorClass<TerrainTypeClass *> vtable 0x007a2724 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TerrainTypeClass;

template class DynamicVectorClass<TerrainTypeClass *>;
