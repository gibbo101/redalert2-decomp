// VectorClass<BaseNodeClass>::Clear (0x0042D2A0; VectorClass<BaseNodeClass> vtable 0x0079c600 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class BaseNodeClass;

template class VectorClass<BaseNodeClass>;
