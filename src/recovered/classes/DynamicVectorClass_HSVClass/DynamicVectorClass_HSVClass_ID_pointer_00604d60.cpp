// DynamicVectorClass<HSVClass>::ID_pointer (0x00604D60; DynamicVectorClass<HSVClass> vtable 0x007a7b58 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// HSVClass is a size-only stand-in (3 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_DYNAMIC_ID_POINTER
#include "shared/vector_class.hpp"

struct HSVClass {
    unsigned char unknown[3];
};

template class DynamicVectorClass<HSVClass>;
