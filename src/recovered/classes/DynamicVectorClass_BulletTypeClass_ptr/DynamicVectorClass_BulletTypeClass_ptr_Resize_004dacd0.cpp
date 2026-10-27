// DynamicVectorClass<BulletTypeClass *>::Resize (0x004DACD0; DynamicVectorClass<BulletTypeClass *> vtable 0x007a28a4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class BulletTypeClass;

template class DynamicVectorClass<BulletTypeClass *>;
