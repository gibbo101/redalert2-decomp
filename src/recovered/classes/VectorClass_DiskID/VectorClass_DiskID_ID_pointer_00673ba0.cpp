// VectorClass<DiskID>::ID_pointer (0x00673BA0; VectorClass<DiskID> vtable 0x007a9624 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// DiskID is a size-only stand-in (4 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct DiskID {
    int unknown[1];
};

template class VectorClass<DiskID>;
