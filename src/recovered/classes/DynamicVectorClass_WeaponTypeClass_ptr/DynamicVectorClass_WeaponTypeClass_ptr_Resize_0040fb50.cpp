// DynamicVectorClass<WeaponTypeClass *>::Resize (0x0040FB50; DynamicVectorClass<WeaponTypeClass *> vtable 0x0079ad5c slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class WeaponTypeClass;

template class DynamicVectorClass<WeaponTypeClass *>;
