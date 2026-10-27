// DynamicVectorClass<DiskID>::Resize (0x00673BC0; TypeList<DiskID> vtable 0x007a9684 slot 2).
// Layout and behaviour: shared/vector_class.hpp.
// DiskID is a size-only stand-in (4 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_RESIZE
#include "shared/vector_class.hpp"

struct DiskID {
    int unknown[1];
};

template class DynamicVectorClass<DiskID>;
