// VectorClass<HashObject<HashString, SchemeNode *>>::ID_pointer (0x00605A80; VectorClass<HashObject<HashString, SchemeNode *>> vtable 0x007a7bd8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// HashObject<HashString, SchemeNode *> is a size-only stand-in (260 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

class HashString;

class SchemeNode;

template <class A0, class A1>
struct HashObject {
    int unknown[65];
};

template class VectorClass<HashObject<HashString, SchemeNode *> >;
