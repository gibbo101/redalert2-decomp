// VectorClass<FoggedObjectClass *>::Fetch (0x00453DD0; VectorClass<FoggedObjectClass *> vtable 0x0079d19c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class FoggedObjectClass;

template class VectorClass<FoggedObjectClass *>;
