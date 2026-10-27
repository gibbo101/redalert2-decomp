// DynamicVectorClass<AngerStruct>::Clear (0x004F6C60; DynamicVectorClass<AngerStruct> vtable 0x007a2e64 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct AngerStruct;

template class DynamicVectorClass<AngerStruct>;
