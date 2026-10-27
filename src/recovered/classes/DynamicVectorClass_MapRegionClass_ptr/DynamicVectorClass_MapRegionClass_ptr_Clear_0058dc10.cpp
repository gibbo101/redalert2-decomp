// DynamicVectorClass<MapRegionClass *>::Clear (0x0058DC10; DynamicVectorClass<MapRegionClass *> vtable 0x007a5d90 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class MapRegionClass;

template class DynamicVectorClass<MapRegionClass *>;
