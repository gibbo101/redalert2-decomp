// DynamicVectorClass<HouseClass *>::Clear (0x004D5010; DynamicVectorClass<HouseClass *> vtable 0x007a2424 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class HouseClass;

template class DynamicVectorClass<HouseClass *>;
