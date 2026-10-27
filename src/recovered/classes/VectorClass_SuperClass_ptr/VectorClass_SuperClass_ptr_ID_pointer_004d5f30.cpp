// VectorClass<SuperClass *>::ID_pointer (0x004D5F30; VectorClass<SuperClass *> vtable 0x007a2a44 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class SuperClass;

template class VectorClass<SuperClass *>;
