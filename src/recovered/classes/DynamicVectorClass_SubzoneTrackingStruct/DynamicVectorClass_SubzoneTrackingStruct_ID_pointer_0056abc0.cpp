// DynamicVectorClass<SubzoneTrackingStruct>::ID_pointer (0x0056ABC0; DynamicVectorClass<SubzoneTrackingStruct> vtable 0x007a59d8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// SubzoneTrackingStruct is a size-only stand-in (36 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct SubzoneTrackingStruct {
    int unknown[9];
};

template class DynamicVectorClass<SubzoneTrackingStruct>;
