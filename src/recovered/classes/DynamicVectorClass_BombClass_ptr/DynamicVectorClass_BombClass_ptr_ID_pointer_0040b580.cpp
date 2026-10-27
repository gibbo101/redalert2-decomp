// DynamicVectorClass<BombClass *>::ID_pointer (0x0040B580; DynamicVectorClass<BombClass *> vtable 0x0079a7bc slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class BombClass;

template class DynamicVectorClass<BombClass *>;
