// DynamicVectorClass<HashObject<unsigned int, unsigned int>>::ID_pointer (0x0056AD70; DynamicVectorClass<HashObject<unsigned int, unsigned int>> vtable 0x007a5a78 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// HashObject<unsigned int, unsigned int> is a size-only stand-in (8 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

template <class A0, class A1>
struct HashObject {
    int unknown[2];
};

template class DynamicVectorClass<HashObject<unsigned int, unsigned int> >;
