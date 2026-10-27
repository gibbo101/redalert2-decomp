// DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>>::ID_pointer (0x0056ADE0; DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct>> vtable 0x007a5a58 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// HashObject<unsigned int, SubzoneConnectionStruct> is a size-only stand-in (12 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

class SubzoneConnectionStruct;

template <class A0, class A1>
struct HashObject {
    int unknown[3];
};

template class DynamicVectorClass<HashObject<unsigned int, SubzoneConnectionStruct> >;
