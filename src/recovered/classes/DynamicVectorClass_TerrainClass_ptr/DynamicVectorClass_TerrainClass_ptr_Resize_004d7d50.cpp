// DynamicVectorClass<TerrainClass *>::Resize (0x004D7D50; DynamicVectorClass<TerrainClass *> vtable 0x007a2324 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class TerrainClass;

template class DynamicVectorClass<TerrainClass *>;
