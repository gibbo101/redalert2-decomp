// DynamicVectorClass<BulletClass *>::ID_object (0x004641D0; DynamicVectorClass<BulletClass *> vtable 0x0079d308 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class BulletClass;

template class DynamicVectorClass<BulletClass *>;
