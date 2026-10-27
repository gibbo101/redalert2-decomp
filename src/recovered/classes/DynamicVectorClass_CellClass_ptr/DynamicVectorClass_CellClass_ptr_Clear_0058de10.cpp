// DynamicVectorClass<CellClass *>::Clear (0x0058DE10; DynamicVectorClass<CellClass *> vtable 0x007a5efc slot 3).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class CellClass;

template class DynamicVectorClass<CellClass *>;
