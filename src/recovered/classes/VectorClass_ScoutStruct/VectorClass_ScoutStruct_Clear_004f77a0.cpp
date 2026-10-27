// VectorClass<ScoutStruct>::Clear (0x004F77A0; VectorClass<ScoutStruct> vtable 0x007a2ea4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct ScoutStruct;

template class VectorClass<ScoutStruct>;
