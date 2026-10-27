// VectorClass<ObjectClass *>::operator equal (0x0040CBC0; VectorClass<ObjectClass *> vtable 0x0079a91c slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class ObjectClass;

template class VectorClass<ObjectClass *>;
