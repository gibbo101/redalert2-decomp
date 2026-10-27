// DynamicVectorClass<BulletTypeClass *>::ID_object (0x004DAD80; DynamicVectorClass<BulletTypeClass *> vtable 0x007a28a4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class BulletTypeClass;

template class DynamicVectorClass<BulletTypeClass *>;
