// DynamicVectorClass<CellClass *>::ID_object (0x0058E930; DynamicVectorClass<CellClass *> vtable 0x007a5efc slot 4).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_OBJECT
#include "shared/vector_class.hpp"

class CellClass;

template class DynamicVectorClass<CellClass *>;
