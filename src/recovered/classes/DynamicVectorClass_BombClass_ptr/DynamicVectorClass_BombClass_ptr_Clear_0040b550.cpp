// DynamicVectorClass<BombClass *>::Clear (0x0040B550; DynamicVectorClass<BombClass *> vtable 0x0079a7bc slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class BombClass;

template class DynamicVectorClass<BombClass *>;
