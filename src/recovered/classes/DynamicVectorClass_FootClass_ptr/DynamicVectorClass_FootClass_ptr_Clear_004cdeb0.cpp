// DynamicVectorClass<FootClass *>::Clear (0x004CDEB0; DynamicVectorClass<FootClass *> vtable 0x007a1234 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class FootClass;

template class DynamicVectorClass<FootClass *>;
