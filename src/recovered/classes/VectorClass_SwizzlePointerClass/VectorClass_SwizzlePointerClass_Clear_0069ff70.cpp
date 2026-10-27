// VectorClass<SwizzlePointerClass>::Clear (0x0069FF70; VectorClass<SwizzlePointerClass> vtable 0x007ac37c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct SwizzlePointerClass;

template class VectorClass<SwizzlePointerClass>;
