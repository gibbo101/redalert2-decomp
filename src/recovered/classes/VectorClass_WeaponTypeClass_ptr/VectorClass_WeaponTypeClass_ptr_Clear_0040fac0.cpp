// VectorClass<WeaponTypeClass *>::Clear (0x0040FAC0; VectorClass<WeaponTypeClass *> vtable 0x0079ad7c slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class WeaponTypeClass;

template class VectorClass<WeaponTypeClass *>;
