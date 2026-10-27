// DynamicVectorClass<MapRegionClass *>::Resize (0x0058E090; DynamicVectorClass<MapRegionClass *> vtable 0x007a5d90 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class MapRegionClass;

template class DynamicVectorClass<MapRegionClass *>;
