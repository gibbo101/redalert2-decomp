// DynamicVectorClass<ZoneConnectionClass>::Clear (0x0056AAC0; DynamicVectorClass<ZoneConnectionClass> vtable 0x007a59f8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct ZoneConnectionClass;

template class DynamicVectorClass<ZoneConnectionClass>;
