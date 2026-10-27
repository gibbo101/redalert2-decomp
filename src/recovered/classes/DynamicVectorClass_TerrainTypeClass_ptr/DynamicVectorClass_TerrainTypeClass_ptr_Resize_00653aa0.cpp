// DynamicVectorClass<TerrainTypeClass *>::Resize (0x00653AA0; TypeList<TerrainTypeClass *> vtable 0x007a90b8 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class TerrainTypeClass;

template class DynamicVectorClass<TerrainTypeClass *>;
