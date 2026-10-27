// DynamicVectorClass<SuperWeaponTypeClass *>::ID_pointer (0x004D5880; DynamicVectorClass<SuperWeaponTypeClass *> vtable 0x007a29e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class SuperWeaponTypeClass;

template class DynamicVectorClass<SuperWeaponTypeClass *>;
