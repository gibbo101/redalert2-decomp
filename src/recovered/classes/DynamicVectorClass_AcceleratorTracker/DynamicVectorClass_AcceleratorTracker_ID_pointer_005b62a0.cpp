// DynamicVectorClass<AcceleratorTracker>::ID_pointer (0x005B62A0; DynamicVectorClass<AcceleratorTracker> vtable 0x007a7124 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// AcceleratorTracker is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct AcceleratorTracker {
    int unknown[2];
};

template class DynamicVectorClass<AcceleratorTracker>;
