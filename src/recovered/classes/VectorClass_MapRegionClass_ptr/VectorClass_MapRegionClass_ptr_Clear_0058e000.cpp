// VectorClass<MapRegionClass *>::Clear (0x0058E000; VectorClass<MapRegionClass *> vtable 0x007a5db0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class MapRegionClass;

template class VectorClass<MapRegionClass *>;
