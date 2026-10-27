// DynamicVectorClass<BulletTypeClass *>::ID_pointer (0x004D56A0; DynamicVectorClass<BulletTypeClass *> vtable 0x007a28a4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class BulletTypeClass;

template class DynamicVectorClass<BulletTypeClass *>;
