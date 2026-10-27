// VectorClass<SubzoneConnectionStruct>::ID_pointer (0x0040B210; VectorClass<SubzoneConnectionStruct> vtable 0x0079a76c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// SubzoneConnectionStruct is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct SubzoneConnectionStruct {
    int unknown[2];
};

template class VectorClass<SubzoneConnectionStruct>;
