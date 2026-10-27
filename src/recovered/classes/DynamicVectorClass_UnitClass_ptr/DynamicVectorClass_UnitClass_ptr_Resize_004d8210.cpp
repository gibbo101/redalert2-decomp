// DynamicVectorClass<UnitClass *>::Resize (0x004D8210; DynamicVectorClass<UnitClass *> vtable 0x007a23e4 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class UnitClass;

template class DynamicVectorClass<UnitClass *>;
