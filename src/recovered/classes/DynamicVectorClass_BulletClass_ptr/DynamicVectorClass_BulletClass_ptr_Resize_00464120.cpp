// DynamicVectorClass<BulletClass *>::Resize (0x00464120; DynamicVectorClass<BulletClass *> vtable 0x0079d308 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class BulletClass;

template class DynamicVectorClass<BulletClass *>;
