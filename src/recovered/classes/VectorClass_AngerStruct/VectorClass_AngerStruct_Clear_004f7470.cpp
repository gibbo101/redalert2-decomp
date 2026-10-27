// VectorClass<AngerStruct>::Clear (0x004F7470; VectorClass<AngerStruct> vtable 0x007a2e84 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct AngerStruct;

template class VectorClass<AngerStruct>;
