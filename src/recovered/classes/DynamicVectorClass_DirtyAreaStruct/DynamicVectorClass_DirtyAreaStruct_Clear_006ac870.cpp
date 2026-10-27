// DynamicVectorClass<DirtyAreaStruct>::Clear (0x006AC870; DynamicVectorClass<DirtyAreaStruct> vtable 0x007ac4c4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct DirtyAreaStruct;

template class DynamicVectorClass<DirtyAreaStruct>;
