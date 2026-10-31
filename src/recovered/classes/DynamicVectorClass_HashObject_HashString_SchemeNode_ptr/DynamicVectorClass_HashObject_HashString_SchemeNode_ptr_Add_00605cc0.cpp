// DynamicVectorClass<HashObject<HashString, SchemeNode *>>::Add (0x00605CC0).
// Layout and behaviour: shared/vector_class.hpp, element shared/hash_string.hpp
// (0x00603577 adds a color scheme's hash entry).
// @ref ??4HashString@@QAEAAV0@ABV0@@Z=004e11c0
#define VECTOR_IMPLEMENT_DYNAMIC_ADD
#define VECTOR_IMPLEMENT_VECTOR_ACCESSORS
#include "shared/vector_class.hpp"
#include "shared/hash_string.hpp"

template class DynamicVectorClass<HashObject<HashString, SchemeNode *> >;
