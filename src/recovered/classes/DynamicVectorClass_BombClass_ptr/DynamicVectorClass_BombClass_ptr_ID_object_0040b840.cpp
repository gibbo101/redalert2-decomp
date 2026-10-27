// DynamicVectorClass<BombClass *>::ID_object (0x0040B840; DynamicVectorClass<BombClass *> vtable 0x0079a7bc slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class BombClass;

template class DynamicVectorClass<BombClass *>;
