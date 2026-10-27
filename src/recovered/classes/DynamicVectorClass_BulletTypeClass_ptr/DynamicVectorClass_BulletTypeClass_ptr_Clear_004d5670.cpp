// DynamicVectorClass<BulletTypeClass *>::Clear (0x004D5670; DynamicVectorClass<BulletTypeClass *> vtable 0x007a28a4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class BulletTypeClass;

template class DynamicVectorClass<BulletTypeClass *>;
