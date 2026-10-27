// DynamicVectorClass<SwizzlePointerClass>::ID_pointer (0x0069FE00; DynamicVectorClass<SwizzlePointerClass> vtable 0x007ac35c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// SwizzlePointerClass is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct SwizzlePointerClass {
    int unknown[2];
};

template class DynamicVectorClass<SwizzlePointerClass>;
