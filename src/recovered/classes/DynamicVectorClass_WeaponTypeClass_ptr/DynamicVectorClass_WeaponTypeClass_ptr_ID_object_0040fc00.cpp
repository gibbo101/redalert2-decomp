// DynamicVectorClass<WeaponTypeClass *>::ID_object (0x0040FC00; DynamicVectorClass<WeaponTypeClass *> vtable 0x0079ad5c slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class WeaponTypeClass;

template class DynamicVectorClass<WeaponTypeClass *>;
