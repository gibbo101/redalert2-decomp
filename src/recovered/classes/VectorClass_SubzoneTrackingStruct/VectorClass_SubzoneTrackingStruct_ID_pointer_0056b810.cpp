// VectorClass<SubzoneTrackingStruct>::ID_pointer (0x0056B810; VectorClass<SubzoneTrackingStruct> vtable 0x007a5a38 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// SubzoneTrackingStruct is a size-only stand-in (36 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct SubzoneTrackingStruct {
    int unknown[9];
};

template class VectorClass<SubzoneTrackingStruct>;
