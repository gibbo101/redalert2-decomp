// DynamicVectorClass<SwizzlePointerClass>::Clear (0x0069FDD0; DynamicVectorClass<SwizzlePointerClass> vtable 0x007ac35c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct SwizzlePointerClass;

template class DynamicVectorClass<SwizzlePointerClass>;
