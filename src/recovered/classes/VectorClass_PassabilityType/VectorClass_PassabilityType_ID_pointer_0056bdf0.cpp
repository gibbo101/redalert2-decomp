// VectorClass<PassabilityType>::ID_pointer (0x0056BDF0; VectorClass<PassabilityType> vtable 0x007a5a98 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// PassabilityType is a size-only stand-in (4 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct PassabilityType {
    int unknown[1];
};

template class VectorClass<PassabilityType>;
