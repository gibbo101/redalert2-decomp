// VectorClass<UnitClass *>::Fetch (0x004D5000; VectorClass<UnitClass *> vtable 0x007a2404 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class UnitClass;

template class VectorClass<UnitClass *>;
