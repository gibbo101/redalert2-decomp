// DynamicVectorClass<Cell>::Clear (0x0042CC10; DynamicVectorClass<Cell> vtable 0x0079c5a0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

class Cell;

template class DynamicVectorClass<Cell>;
