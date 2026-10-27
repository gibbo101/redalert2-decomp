// DynamicVectorClass<SuperWeaponTypeClass *>::Resize (0x004DB8B0; DynamicVectorClass<SuperWeaponTypeClass *> vtable 0x007a29e4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class SuperWeaponTypeClass;

template class DynamicVectorClass<SuperWeaponTypeClass *>;
