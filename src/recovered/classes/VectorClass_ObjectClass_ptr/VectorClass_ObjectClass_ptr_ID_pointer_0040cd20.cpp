// VectorClass<ObjectClass *>::ID_pointer (0x0040CD20; VectorClass<ObjectClass *> vtable 0x0079a91c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class ObjectClass;

template class VectorClass<ObjectClass *>;
