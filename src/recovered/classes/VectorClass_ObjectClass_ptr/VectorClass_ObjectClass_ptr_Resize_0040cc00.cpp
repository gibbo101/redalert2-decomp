// VectorClass<ObjectClass *>::Resize (0x0040CC00; VectorClass<ObjectClass *> vtable 0x0079a91c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

class ObjectClass;

template class VectorClass<ObjectClass *>;
