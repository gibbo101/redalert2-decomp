// VectorClass<AbstractClass *>::ID_object (0x004CE100; VectorClass<AbstractClass *> vtable 0x007a179c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_OBJECT
#include "shared/vector_class.hpp"

class AbstractClass;

template class VectorClass<AbstractClass *>;
