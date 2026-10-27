// VectorClass<ObjectClass *>::Fetch (0x0040CBB0; VectorClass<ObjectClass *> vtable 0x0079a91c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class ObjectClass;

template class VectorClass<ObjectClass *>;
