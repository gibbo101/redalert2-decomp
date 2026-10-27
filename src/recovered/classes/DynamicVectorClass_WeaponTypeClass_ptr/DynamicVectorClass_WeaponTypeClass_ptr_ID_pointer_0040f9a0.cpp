// DynamicVectorClass<WeaponTypeClass *>::ID_pointer (0x0040F9A0; DynamicVectorClass<WeaponTypeClass *> vtable 0x0079ad5c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class WeaponTypeClass;

template class DynamicVectorClass<WeaponTypeClass *>;
