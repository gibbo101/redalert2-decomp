// DynamicVectorClass<Cell>::ID_pointer (0x0042CC40; DynamicVectorClass<Cell> vtable 0x0079c5a0 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// Cell is a size-only stand-in (4 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class Cell {
public:
    int unknown[1];
};

template class DynamicVectorClass<Cell>;
