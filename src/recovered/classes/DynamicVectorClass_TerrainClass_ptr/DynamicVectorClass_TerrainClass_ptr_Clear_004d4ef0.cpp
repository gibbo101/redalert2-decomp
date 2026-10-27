// DynamicVectorClass<TerrainClass *>::Clear (0x004D4EF0; DynamicVectorClass<TerrainClass *> vtable 0x007a2324 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TerrainClass;

template class DynamicVectorClass<TerrainClass *>;
