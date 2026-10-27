// VectorClass<AbstractClass *>::Clear (0x004CE0D0; VectorClass<AbstractClass *> vtable 0x007a179c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class AbstractClass;

template class VectorClass<AbstractClass *>;
