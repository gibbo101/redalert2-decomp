// VectorClass<FoggedObjectClass::DrawRecord>::Clear (0x004C2290; VectorClass<FoggedObjectClass::DrawRecord> vtable 0x007a11d0 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class FoggedObjectClass {
public:
    struct DrawRecord;
};

template class VectorClass<FoggedObjectClass::DrawRecord>;
