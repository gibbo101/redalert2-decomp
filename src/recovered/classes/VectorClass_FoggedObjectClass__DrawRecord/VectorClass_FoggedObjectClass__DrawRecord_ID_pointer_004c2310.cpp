// VectorClass<FoggedObjectClass::DrawRecord>::ID_pointer (0x004C2310; VectorClass<FoggedObjectClass::DrawRecord> vtable 0x007a11d0 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// FoggedObjectClass::DrawRecord is a size-only stand-in (16 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class FoggedObjectClass {
public:
    struct DrawRecord {
        int unknown[4];
    };
};

template class VectorClass<FoggedObjectClass::DrawRecord>;
