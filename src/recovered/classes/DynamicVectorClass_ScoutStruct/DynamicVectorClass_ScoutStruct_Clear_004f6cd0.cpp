// DynamicVectorClass<ScoutStruct>::Clear (0x004F6CD0; DynamicVectorClass<ScoutStruct> vtable 0x007a2e44 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct ScoutStruct;

template class DynamicVectorClass<ScoutStruct>;
