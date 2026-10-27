// VectorClass<HSVClass>::ID_pointer (0x00605420; VectorClass<HSVClass> vtable 0x007a7bf8 slot 5).
// Layout and behaviour: shared/vector_class.hpp.
// HSVClass is a size-only stand-in (3 bytes, from the ID(T const *) divisor);
// its real fields are not recovered.
#define VECTOR_IMPLEMENT_VECTOR_ID_POINTER
#include "shared/vector_class.hpp"

struct HSVClass {
    unsigned char unknown[3];
};

template class VectorClass<HSVClass>;
