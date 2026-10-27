// DynamicVectorClass<HSVClass>::Clear (0x00604D30; DynamicVectorClass<HSVClass> vtable 0x007a7b58 slot 3).
// Layout and behaviour: shared/vector_class.hpp.
// The element type is left incomplete: Clear does not depend on it.
#define VECTOR_IMPLEMENT_DYNAMIC_CLEAR
#include "shared/vector_class.hpp"

struct HSVClass;

template class DynamicVectorClass<HSVClass>;
