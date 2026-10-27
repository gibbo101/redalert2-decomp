// VectorClass<RGBClass>::Clear (0x0046D880; VectorClass<RGBClass> vtable 0x0079da54 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct RGBClass;

template class VectorClass<RGBClass>;
