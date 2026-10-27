// DynamicVectorClass<CellClass *>::Resize (0x0058E880; DynamicVectorClass<CellClass *> vtable 0x007a5efc slot 2).
// Layout and behaviour: shared/vector_class.hpp.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

class CellClass;

template class DynamicVectorClass<CellClass *>;
