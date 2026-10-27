// VectorClass<ObjectClass *>::ID_object (0x0040CCE0; VectorClass<ObjectClass *> vtable 0x0079a91c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class ObjectClass;

template class VectorClass<ObjectClass *>;
