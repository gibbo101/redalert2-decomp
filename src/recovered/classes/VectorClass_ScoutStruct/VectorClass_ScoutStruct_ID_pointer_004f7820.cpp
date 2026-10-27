// VectorClass<ScoutStruct>::ID_pointer (0x004F7820; VectorClass<ScoutStruct> vtable 0x007a2ea4 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// ScoutStruct is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct ScoutStruct {
    int unknown[2];
};

template class VectorClass<ScoutStruct>;
