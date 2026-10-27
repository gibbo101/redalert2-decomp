// DynamicVectorClass<SuperWeaponTypeClass *>::Clear (0x004D5850; DynamicVectorClass<SuperWeaponTypeClass *> vtable 0x007a29e4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class SuperWeaponTypeClass;

template class DynamicVectorClass<SuperWeaponTypeClass *>;
