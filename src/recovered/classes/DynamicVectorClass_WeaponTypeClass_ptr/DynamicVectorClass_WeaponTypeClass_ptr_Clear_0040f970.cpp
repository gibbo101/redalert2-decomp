// DynamicVectorClass<WeaponTypeClass *>::Clear (0x0040F970; DynamicVectorClass<WeaponTypeClass *> vtable 0x0079ad5c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class WeaponTypeClass;

template class DynamicVectorClass<WeaponTypeClass *>;
