// DynamicVectorClass<DiskID>::Clear (0x006737D0; TypeList<DiskID> vtable 0x007a9684 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct DiskID;

template class DynamicVectorClass<DiskID>;
