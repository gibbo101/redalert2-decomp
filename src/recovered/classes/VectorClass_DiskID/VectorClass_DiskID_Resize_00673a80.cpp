// VectorClass<DiskID>::Resize (0x00673A80; VectorClass<DiskID> vtable 0x007a9624 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
// DiskID is a size-only stand-in (4 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_RESIZE
#include "shared/vector_class.hpp"

struct DiskID {
    int unknown[1];
};

template class VectorClass<DiskID>;
