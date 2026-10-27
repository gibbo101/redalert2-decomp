// VectorClass<Cell>::Clear (0x0042CFB0; VectorClass<Cell> vtable 0x0079c5e0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class Cell;

template class VectorClass<Cell>;
