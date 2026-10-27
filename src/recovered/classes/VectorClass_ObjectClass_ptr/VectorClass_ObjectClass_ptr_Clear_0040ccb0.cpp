// VectorClass<ObjectClass *>::Clear (0x0040CCB0; VectorClass<ObjectClass *> vtable 0x0079a91c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class ObjectClass;

template class VectorClass<ObjectClass *>;
