// VectorClass<SwizzlePointerClass>::Fetch (0x0069FE20; VectorClass<SwizzlePointerClass> vtable 0x007ac37c slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// SwizzlePointerClass is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

struct SwizzlePointerClass {
    int unknown[2];
};

template class VectorClass<SwizzlePointerClass>;
