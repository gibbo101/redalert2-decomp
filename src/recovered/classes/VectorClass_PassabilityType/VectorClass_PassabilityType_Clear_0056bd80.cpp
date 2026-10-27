// VectorClass<PassabilityType>::Clear (0x0056BD80; VectorClass<PassabilityType> vtable 0x007a5a98 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct PassabilityType;

template class VectorClass<PassabilityType>;
