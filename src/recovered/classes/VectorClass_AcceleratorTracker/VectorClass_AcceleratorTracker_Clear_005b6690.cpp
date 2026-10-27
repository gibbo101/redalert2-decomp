// VectorClass<AcceleratorTracker>::Clear (0x005B6690; VectorClass<AcceleratorTracker> vtable 0x007a7144 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct AcceleratorTracker;

template class VectorClass<AcceleratorTracker>;
