// DynamicVectorClass<UndoInfoStruct>::ID_pointer (0x00686F70; DynamicVectorClass<UndoInfoStruct> vtable 0x007ab50c slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// UndoInfoStruct is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct UndoInfoStruct {
    int unknown[3];
};

template class DynamicVectorClass<UndoInfoStruct>;
