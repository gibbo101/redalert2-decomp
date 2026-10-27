// DynamicVectorClass<AngerStruct>::ID_pointer (0x004F6C90; DynamicVectorClass<AngerStruct> vtable 0x007a2e64 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// AngerStruct is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct AngerStruct {
    int unknown[2];
};

template class DynamicVectorClass<AngerStruct>;
