// DynamicVectorClass<SpotLightClass *>::Clear (0x005DE300; DynamicVectorClass<SpotLightClass *> vtable 0x007a7ac4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class SpotLightClass;

template class DynamicVectorClass<SpotLightClass *>;
