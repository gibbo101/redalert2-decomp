// VectorClass<SuperClass *>::operator equal (0x004D5DD0; VectorClass<SuperClass *> vtable 0x007a2a44 slot 1).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_EQUAL
#include "shared/vector_class.hpp"

class SuperClass;

template class VectorClass<SuperClass *>;
