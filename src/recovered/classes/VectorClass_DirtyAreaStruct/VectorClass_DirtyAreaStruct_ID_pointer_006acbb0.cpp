// VectorClass<DirtyAreaStruct>::ID_pointer (0x006ACBB0; VectorClass<DirtyAreaStruct> vtable 0x007ac4e4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// DirtyAreaStruct is a size-only stand-in (20 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct DirtyAreaStruct {
    int unknown[5];
};

template class VectorClass<DirtyAreaStruct>;
