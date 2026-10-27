// VectorClass<HSVClass>::Fetch (0x00604D90; VectorClass<HSVClass> vtable 0x007a7bf8 slot 6).
// Layout and behaviour: shared/vector_class.hpp.
// HSVClass is a size-only stand-in (3 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_FETCH
#include "shared/vector_class.hpp"

struct HSVClass {
    unsigned char unknown[3];
};

template class VectorClass<HSVClass>;
