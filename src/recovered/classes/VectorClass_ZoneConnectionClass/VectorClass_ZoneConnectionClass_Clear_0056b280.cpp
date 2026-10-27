// VectorClass<ZoneConnectionClass>::Clear (0x0056B280; VectorClass<ZoneConnectionClass> vtable 0x007a5a18 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct ZoneConnectionClass;

template class VectorClass<ZoneConnectionClass>;
