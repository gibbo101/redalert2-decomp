// VectorClass<ZoneConnectionClass>::ID_pointer (0x0056B310; VectorClass<ZoneConnectionClass> vtable 0x007a5a18 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// ZoneConnectionClass is a size-only stand-in (16 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct ZoneConnectionClass {
    int unknown[4];
};

template class VectorClass<ZoneConnectionClass>;
