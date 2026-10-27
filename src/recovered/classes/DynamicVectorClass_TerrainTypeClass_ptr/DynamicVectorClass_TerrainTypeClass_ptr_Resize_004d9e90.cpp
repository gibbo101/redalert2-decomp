// DynamicVectorClass<TerrainTypeClass *>::Resize (0x004D9E90; DynamicVectorClass<TerrainTypeClass *> vtable 0x007a2724 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class TerrainTypeClass;

template class DynamicVectorClass<TerrainTypeClass *>;
