// VectorClass<AcceleratorTracker>::Fetch (0x005B62C0; VectorClass<AcceleratorTracker> vtable 0x007a7144 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// AcceleratorTracker is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

struct AcceleratorTracker {
    int unknown[2];
};

template class VectorClass<AcceleratorTracker>;
