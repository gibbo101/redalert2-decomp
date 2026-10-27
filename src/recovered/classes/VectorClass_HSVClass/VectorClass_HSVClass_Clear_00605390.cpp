// VectorClass<HSVClass>::Clear (0x00605390; VectorClass<HSVClass> vtable 0x007a7bf8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct HSVClass;

template class VectorClass<HSVClass>;
