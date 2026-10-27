// VectorClass<SuperClass *>::Fetch (0x004D4AB0; VectorClass<SuperClass *> vtable 0x007a2a44 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class SuperClass;

template class VectorClass<SuperClass *>;
