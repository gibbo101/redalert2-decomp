// DynamicVectorClass<HouseTypeClass *>::Clear (0x004D51F0; DynamicVectorClass<HouseTypeClass *> vtable 0x007a25a4 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class HouseTypeClass;

template class DynamicVectorClass<HouseTypeClass *>;
