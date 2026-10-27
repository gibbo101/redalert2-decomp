// VectorClass<AbstractClass *>::Fetch (0x004CDE80; VectorClass<AbstractClass *> vtable 0x007a179c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

class AbstractClass;

template class VectorClass<AbstractClass *>;
