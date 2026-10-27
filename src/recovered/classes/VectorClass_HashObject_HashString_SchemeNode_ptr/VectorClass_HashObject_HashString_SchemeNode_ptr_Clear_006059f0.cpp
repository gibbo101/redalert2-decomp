// VectorClass<HashObject<HashString, SchemeNode *>>::Clear (0x006059F0; VectorClass<HashObject<HashString, SchemeNode *>> vtable 0x007a7bd8 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_VECTOR_CLEAR
#include "shared/vector_class.hpp"

class HashString;

class SchemeNode;

template <class A0, class A1>
struct HashObject;

template class VectorClass<HashObject<HashString, SchemeNode *> >;
