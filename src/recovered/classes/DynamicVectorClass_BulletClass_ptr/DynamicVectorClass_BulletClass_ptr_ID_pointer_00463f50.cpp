// DynamicVectorClass<BulletClass *>::ID_pointer (0x00463F50; DynamicVectorClass<BulletClass *> vtable 0x0079d308 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class BulletClass;

template class DynamicVectorClass<BulletClass *>;
