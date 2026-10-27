// VectorClass<UndoInfoStruct>::Fetch (0x00686FA0; VectorClass<UndoInfoStruct> vtable 0x007ab52c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// UndoInfoStruct is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

struct UndoInfoStruct {
    int unknown[3];
};

template class VectorClass<UndoInfoStruct>;
