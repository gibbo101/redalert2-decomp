// VectorClass<DiskID>::Clear (0x00673B30; VectorClass<DiskID> vtable 0x007a9624 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

struct DiskID;

template class VectorClass<DiskID>;
