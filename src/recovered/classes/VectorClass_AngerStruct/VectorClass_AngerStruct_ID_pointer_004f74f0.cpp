// VectorClass<AngerStruct>::ID_pointer (0x004F74F0; VectorClass<AngerStruct> vtable 0x007a2e84 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// AngerStruct is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct AngerStruct {
    int unknown[2];
};

template class VectorClass<AngerStruct>;
