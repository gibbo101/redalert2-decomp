// DynamicVectorClass<BulletClass *>::Clear (0x00463F20; DynamicVectorClass<BulletClass *> vtable 0x0079d308 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class BulletClass;

template class DynamicVectorClass<BulletClass *>;
