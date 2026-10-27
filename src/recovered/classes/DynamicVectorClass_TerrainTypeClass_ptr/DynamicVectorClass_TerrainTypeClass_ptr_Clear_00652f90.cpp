// DynamicVectorClass<TerrainTypeClass *>::Clear (0x00652F90; TypeList<TerrainTypeClass *> vtable 0x007a90b8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class TerrainTypeClass;

template class DynamicVectorClass<TerrainTypeClass *>;
