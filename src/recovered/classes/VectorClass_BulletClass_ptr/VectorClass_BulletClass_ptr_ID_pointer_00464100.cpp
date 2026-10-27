// VectorClass<BulletClass *>::ID_pointer (0x00464100; VectorClass<BulletClass *> vtable 0x0079d328 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class BulletClass;

template class VectorClass<BulletClass *>;
