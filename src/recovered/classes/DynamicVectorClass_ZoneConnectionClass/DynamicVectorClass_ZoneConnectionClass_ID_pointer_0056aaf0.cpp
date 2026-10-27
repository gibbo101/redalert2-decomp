// DynamicVectorClass<ZoneConnectionClass>::ID_pointer (0x0056AAF0; DynamicVectorClass<ZoneConnectionClass> vtable 0x007a59f8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// ZoneConnectionClass is a size-only stand-in (16 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct ZoneConnectionClass {
    int unknown[4];
};

template class DynamicVectorClass<ZoneConnectionClass>;
