// DynamicVectorClass<SuperWeaponTypeClass *>::ID_object (0x004DB960; DynamicVectorClass<SuperWeaponTypeClass *> vtable 0x007a29e4 slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class SuperWeaponTypeClass;

template class DynamicVectorClass<SuperWeaponTypeClass *>;
